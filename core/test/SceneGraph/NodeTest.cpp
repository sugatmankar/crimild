/*
 * Copyright (c) 2013, Hernan Saez
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "SceneGraph/Node.hpp"
#include "SceneGraph/Group.hpp"

#include "Utils/MockComponent.hpp"

#include "gtest/gtest.h"

using namespace crimild;

TEST( NodeTest, construction )
{
	Pointer< Node > node( new Node( "a Node" ) );

	EXPECT_EQ( node->getName(), "a Node" );
	EXPECT_FALSE( node->hasParent() );
	EXPECT_EQ( node->getParent(), nullptr );
}

TEST( NodeTest, destruction )
{
	Pointer< MockComponent > cmp1( new MockComponent() );
	EXPECT_CALL( *( cmp1.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );
	EXPECT_CALL( *( cmp1.get() ), onDetach() )
		.Times( ::testing::Exactly( 1 ) );

	{
		Pointer< Node > node( new Node() );
		node->attachComponent( cmp1.get() );

		EXPECT_EQ( node->getComponent< MockComponent >(), cmp1.get() );
	}

	EXPECT_EQ( cmp1->getNode(), nullptr );
}

TEST( NodeTest, setParent )
{
	Pointer< Node > parent( new Node( "the parent" ) );
	Pointer< Node > child( new Node( "the child" ) );

	EXPECT_FALSE( parent->hasParent() );
	EXPECT_EQ( parent->getParent(), nullptr );

	EXPECT_FALSE( child->hasParent() );
	EXPECT_EQ( child->getParent(), nullptr );

	child->setParent( parent.get() );

	EXPECT_TRUE( child->hasParent() );
	ASSERT_NE( child->getParent(), nullptr );
	EXPECT_EQ( child->getParent(), parent.get() );
	EXPECT_EQ( child->getParent()->getName(), parent->getName() );
}

TEST( NodeTest, attachComponent )
{
	Pointer< Node > node( new Node() );

	Pointer< MockComponent > cmp( new MockComponent() );
	EXPECT_CALL( *( cmp.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );

	node->attachComponent( cmp.get() );

	ASSERT_EQ( cmp->getNode(), node.get() );
	ASSERT_EQ( node->getComponent< MockComponent >(), cmp.get() );
}

TEST( NodeTest, attachComponentTwice )
{
	Pointer< Node > node( new Node() );

	Pointer< MockComponent > cmp( new MockComponent() );
	EXPECT_CALL( *( cmp.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );

	node->attachComponent( cmp.get() );
	node->attachComponent( cmp.get() );
}

TEST( NodeTest, getComponentWithName )
{
	Pointer< Node > node( new Node() );

	Pointer< MockComponent > cmp( new MockComponent() );
	EXPECT_CALL( *( cmp.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );

	node->attachComponent( cmp.get() );

	ASSERT_EQ( cmp->getNode(), node.get() );
	ASSERT_EQ( node->getComponentWithName( cmp->getComponentName() ), cmp.get() );
}

TEST( NodeTest, getInvalidComponent )
{
	Pointer< Node > node( new Node() );

	ASSERT_EQ( node->getComponent< MockComponent >(), nullptr );
}

TEST( NodeTest, attachNewComponentWithSameName )
{
	Pointer< Node > node( new Node() );
	
	Pointer< MockComponent > cmp1( new MockComponent() );
	EXPECT_CALL( *( cmp1.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );
	EXPECT_CALL( *( cmp1.get() ), onDetach() )
		.Times( ::testing::Exactly( 1 ) );

	Pointer< MockComponent > cmp2( new MockComponent() );
	EXPECT_CALL( *( cmp2.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );

	node->attachComponent( cmp1.get() );

	ASSERT_EQ( cmp1->getNode(), node.get() );
	ASSERT_EQ( cmp2->getNode(), nullptr );
	ASSERT_EQ( node->getComponent< MockComponent >(), cmp1.get() );

	node->attachComponent( cmp2.get() );

	ASSERT_EQ( cmp1->getNode(), nullptr );
	ASSERT_EQ( cmp2->getNode(), node.get() );
	ASSERT_EQ( node->getComponent< MockComponent >(), cmp2.get() );
}

TEST( NodeTest, detachComponentWithName )
{
	Pointer< Node > node( new Node() );

	Pointer< MockComponent > cmp( new MockComponent() );
	EXPECT_CALL( *( cmp.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );
	EXPECT_CALL( *( cmp.get() ), onDetach() )
		.Times( ::testing::Exactly( 1 ) );

	node->attachComponent( cmp.get() );
	node->detachComponentWithName( cmp->getComponentName() );

	ASSERT_EQ( cmp->getNode(), nullptr );
	ASSERT_EQ( node->getComponent< MockComponent >(), nullptr );
}

TEST( NodeTest, detachComponent )
{
	Pointer< Node > node( new Node() );

	Pointer< MockComponent > cmp( new MockComponent() );
	EXPECT_CALL( *( cmp.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );
	EXPECT_CALL( *( cmp.get() ), onDetach() )
		.Times( ::testing::Exactly( 1 ) );

	node->attachComponent( cmp.get() );
	node->detachComponent( cmp.get() );

	ASSERT_EQ( cmp->getNode(), nullptr );
	ASSERT_EQ( node->getComponent< MockComponent >(), nullptr );
}

TEST( NodeTest, detachInvalidComponent )
{
	Pointer< Node > node( new Node() );

	Pointer< MockComponent > cmp1( new MockComponent() );
	EXPECT_CALL( *( cmp1.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );

	Pointer< MockComponent > cmp2( new MockComponent() );
	EXPECT_CALL( *( cmp2.get() ), onAttach() )
		.Times( 0 );

	node->attachComponent( cmp1.get() );
	node->detachComponent( cmp2.get() );

	ASSERT_EQ( cmp1->getNode(), node.get() );
	ASSERT_EQ( node->getComponent< MockComponent >(), cmp1.get() );

	ASSERT_EQ( cmp2->getNode(), nullptr );
}

TEST( NodeTest, invokeOnAttach )
{
	Pointer< Node > node( new Node() );

	Pointer< MockComponent > cmp( new MockComponent() );
	EXPECT_CALL( *( cmp.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );

	node->attachComponent( cmp.get() );
}

TEST( NodeTest, invokeOnDetach )
{
	Pointer< Node > node( new Node() );
	
	Pointer< MockComponent > cmp( new MockComponent() );
	EXPECT_CALL( *( cmp.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );
	EXPECT_CALL( *( cmp.get() ), onDetach() )
		.Times( ::testing::Exactly( 1 ) );

	node->attachComponent( cmp.get() );
	node->detachComponent( cmp.get() );
}

TEST( NodeTest, detachAllComponents )
{
	Pointer< Node > node( new Node() );

	Pointer< MockComponent > cmp1( new MockComponent() );
	EXPECT_CALL( *( cmp1.get() ), onAttach() )
		.Times( ::testing::Exactly( 1 ) );
	EXPECT_CALL( *( cmp1.get() ), onDetach() )
		.Times( ::testing::Exactly( 1 ) );
	
	node->attachComponent( cmp1.get() );
	EXPECT_EQ( node->getComponent< MockComponent >(), cmp1.get() );
	EXPECT_EQ( cmp1->getNode(), node.get() );

	node->detachAllComponents();

	EXPECT_EQ( node->getComponent< MockComponent >(), nullptr );
	EXPECT_EQ( cmp1->getNode(), nullptr );
}

TEST( NodeTest, updateComponents )
{
	Pointer< Node > node( new Node() );

	Time t;
	
	Pointer< MockComponent > cmp1( new MockComponent() );
	EXPECT_CALL( *( cmp1.get() ), update( testing::_ ) )
		.Times( ::testing::Exactly( 3 ) );
	
	node->attachComponent( cmp1.get() );

	node->updateComponents( t );
	node->updateComponents( t );
	node->updateComponents( t );
}

TEST( NodeTest, getRootParent )
{
	Pointer< Group > g1( new Group() );
	Pointer< Group > g2( new Group() );
	Pointer< Group > g3( new Group() );

	g1->attachNode( g2.get() );
	g2->attachNode( g3.get() );

	EXPECT_EQ( g1.get(), g3->getRootParent() );
}

