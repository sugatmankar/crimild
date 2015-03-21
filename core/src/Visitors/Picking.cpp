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

#include "Picking.hpp"

#include "SceneGraph/Node.hpp"
#include "SceneGraph/Group.hpp"

using namespace crimild;

Picking::Picking( const Ray3f &tester, Picking::Results &results, FilterType filter )
	: _tester( tester ),
	  _results( results ),
	  _filter( filter )
{

}

Picking::~Picking( void )
{

}

void Picking::traverse( NodePtr const &node )
{
	_results.reset();

	NodeVisitor::traverse( node );

	// sort nodes based on how close the ray is to
	// intersecting the scene of each bounding volume
	_results.sortCandidates( [&]( NodePtr const &first, NodePtr const &second ) -> bool {
        return Distance::compute( _tester, first->getWorldBound()->getCenter() ) <
            Distance::compute( _tester, second->getWorldBound()->getCenter() );
    });
}

void Picking::visitNode( NodePtr const &node )
{
	if ( _filter == nullptr || _filter( node ) ) {
		_results.pushCandidate( node );				
	}
}

void Picking::visitGroup( GroupPtr const &group )
{
	visitNode( group );
	group->foreachNode( [&]( NodePtr const &node ) {
        if ( node->getWorldBound()->testIntersection( _tester ) ) {
            node->accept( *this );
        }
    });
}