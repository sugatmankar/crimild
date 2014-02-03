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

#include "SceneGraph/Group.hpp"
#include "Exceptions/HasParentException.hpp"

#include "gtest/gtest.h"

using namespace crimild;

TEST( GroupNodeTest, construction)
{
	Pointer< Group > group( new Group( "a group" ) );

	EXPECT_EQ( group->getName(), "a group" );
	EXPECT_FALSE( group->hasNodes() );
}

TEST( GroupNodeTest, destruction )
{
	Pointer< Node > child1( new Node( "child 1" ) );
	Pointer< Node > child2( new Node( "child 2" ) );

	{
		Pointer< Group > parent( new Group( "parent" ) );

		parent->attachNode( child1.get() );
		EXPECT_TRUE( child1->hasParent() );
		EXPECT_EQ( child1->getParent(), parent.get() );

		parent->attachNode( child2.get() );
		EXPECT_TRUE( child2->hasParent() );
		EXPECT_EQ( child2->getParent(), parent.get() );
	}

	EXPECT_FALSE( child1->hasParent() );
	EXPECT_EQ( child1->getParent(), nullptr );
	EXPECT_FALSE( child2->hasParent() );
	EXPECT_EQ( child2->getParent(), nullptr );
}

TEST( GroupNodeTest, attachNode )
{
	Pointer< Group > parent( new Group( "parent" ) );

	EXPECT_FALSE( parent->hasNodes() );

	Pointer< Node > child( new Node( "child" ) );
	EXPECT_FALSE( child->hasParent() );
	EXPECT_EQ( child->getParent(), nullptr );

	parent->attachNode( child.get() );

	EXPECT_TRUE( child->hasParent() );
	ASSERT_EQ( child->getParent(), parent.get() );
	EXPECT_TRUE( parent->hasNodes() );

	bool found = false;
	int count = 0;
	parent->foreachNode( [&]( Node *node ) mutable {
		++count;
		if ( child == node ) {
			found = true;
		}
	});

	EXPECT_EQ( count, 1 );
	EXPECT_TRUE( found );
}

TEST( GroupNodeTest, attachMultipleNodes )
{
	Pointer< Group > parent( new Group( "parent" ) );
	
	Pointer< Node > child1( new Node( "child 1" ) );
	Pointer< Node > child2( new Node( "child 2" ) );
	Pointer< Node > child3( new Node( "child 3" ) );

	parent->attachNode( child1.get() );
	parent->attachNode( child2.get() );
	parent->attachNode( child3.get() );

	EXPECT_TRUE( parent->hasNodes() );

	int count = 0;
	parent->foreachNode( [&]( Node *node ) mutable {
		++count;
	});
	EXPECT_EQ( count, 3 );
}

TEST( GroupNodeTest, reattachNodeToSameParent )
{
	Pointer< Group > parent( new Group( "parent" ) );
	Pointer< Node > child( new Node( "child" ) );

	parent->attachNode( child.get() );

	EXPECT_NO_THROW( parent->attachNode( child.get() ) );

	bool found = false;
	int count = 0;
	parent->foreachNode( [&]( Node *node ) mutable {
		++count;
		if ( child == node ) {
			found = true;
		}
	});

	EXPECT_EQ( count, 1 );
	EXPECT_TRUE( found );
}

TEST( GroupNodeTest, reattachNodeToDifferentParent )
{
	Pointer< Group > parent1( new Group( "parent" ) );
	Pointer< Group > parent2( new Group( "another parent" ) );
	Pointer< Node > child( new Node( "child" ) );

	parent1->attachNode( child.get() );

	ASSERT_THROW( parent2->attachNode( child.get() ), HasParentException );
}

TEST( GroupNodeTest, detachNode )
{
	Pointer< Group > parent( new Group( "parent" ) );
	Pointer< Node > child( new Node( "child" ) );

	parent->attachNode( child.get() );
	parent->detachNode( child.get() );

	EXPECT_FALSE( parent->hasNodes() );
	EXPECT_FALSE( child->hasParent() );
	EXPECT_EQ( child->getParent(), nullptr );
}

TEST( GroupNodeTest, detachMultipleNodes )
{
	Pointer< Group > parent( new Group( "parent" ) );
	
	Pointer< Node > child1( new Node( "child 1" ) );
	Pointer< Node > child2( new Node( "child 2" ) );
	Pointer< Node > child3( new Node( "child 3" ) );

	parent->attachNode( child1.get() );
	parent->attachNode( child2.get() );
	parent->attachNode( child3.get() );

	parent->detachNode( child1.get() );
	parent->detachNode( child2.get() );

	EXPECT_TRUE( parent->hasNodes() );

	int count = 0;
	parent->foreachNode( [&]( Node *node ) {
		EXPECT_EQ( node->getName(), child3->getName() );
		++count;
	});
	EXPECT_EQ( count, 1 );
}

TEST( GroupNodeTest, detachNodeFromDifferentParent )
{
	Pointer< Group > parent1( new Group( "parent" ) );
	Pointer< Group > parent2( new Group( "another parent" ) );
	Pointer< Node > child( new Node( "child" ) );

	parent1->attachNode( child.get() );
	parent2->detachNode( child.get() );

	EXPECT_TRUE( child->hasParent() );
	ASSERT_EQ( child->getParent(), parent1.get() );
	EXPECT_TRUE( parent1->hasNodes() );
	EXPECT_FALSE( parent2->hasNodes() );
}

TEST( GroupNodeTest, detachAllNodes )
{
	Pointer< Group > parent( new Group( "parent" ) );
	
	Pointer< Node > child1( new Node( "child 1" ) );
	Pointer< Node > child2( new Node( "child 2" ) );
	Pointer< Node > child3( new Node( "child 3" ) );

	parent->attachNode( child1.get() );
	parent->attachNode( child2.get() );
	parent->attachNode( child3.get() );

	parent->detachAllNodes();

	EXPECT_FALSE( parent->hasNodes() );

	EXPECT_FALSE( child1->hasParent() );
	EXPECT_EQ( child1->getParent(), nullptr );
	EXPECT_FALSE( child2->hasParent() );
	EXPECT_EQ( child2->getParent(), nullptr );
	EXPECT_FALSE( child3->hasParent() );
	EXPECT_EQ( child3->getParent(), nullptr );

	int count = 0;
	parent->foreachNode( [&]( Node *node ) {
		++count;
	});

	EXPECT_EQ( count, 0 );
}

TEST( GroupNodeTest, buildHierarchy )
{
	//		node0
	//		/   \
	//	node1	node2
	//			/	\
	//		node3	node4

	Pointer< Group > node0( new Group( "node0" ) );
	Pointer< Group > node2( new Group( "node2" ) );
	Pointer< Node > node1( new Node( "node1" ) );
	Pointer< Node > node3( new Node( "node3" ) );
	Pointer< Node > node4( new Node( "node4" ) );

	node0->attachNode( node1.get() );
	node0->attachNode( node2.get() );
	node2->attachNode( node3.get() );
	node2->attachNode( node4.get() );

	EXPECT_TRUE( node0->hasNodes() );
	EXPECT_EQ( node1->getParent(), node0.get() );
	EXPECT_EQ( node2->getParent(), node0.get() );

	EXPECT_TRUE( node2->hasNodes() );
	EXPECT_EQ( node3->getParent(), node2.get() );
	EXPECT_EQ( node4->getParent(), node2.get() );
}

