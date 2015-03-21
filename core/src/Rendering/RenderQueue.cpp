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

#include "Rendering/RenderQueue.hpp"

using namespace crimild;

RenderQueue::RenderQueue( void )
{
    
}

RenderQueue::~RenderQueue( void )
{
    
}

void RenderQueue::reset( void )
{
    setCamera( nullptr );
    
    _lights.clear();
    _opaqueObjects.clear();
    _translucentObjects.clear();
    _screenObjects.clear();
}

void RenderQueue::setCamera( CameraPtr const &camera )
{
    _camera = camera;
    if ( _camera != nullptr ) {
        _viewMatrix = _camera->getViewMatrix();
        _projectionMatrix = _camera->getProjectionMatrix();
    }
    else {
        _viewMatrix.makeIdentity();
        _projectionMatrix.makeIdentity();
    }
}

void RenderQueue::push( MaterialPtr const &material, PrimitivePtr const &primitive, GeometryPtr const &geometry, const TransformationImpl &world, bool renderOnScreen )
{
    if ( renderOnScreen ) {
        _screenObjects[ material ][ primitive ].push_back( std::make_pair( geometry, world ) );
    }
    else if ( material->getAlphaState()->isEnabled() || material->getProgram() != nullptr ) {
        _translucentObjects[ material ][ primitive ].push_back( std::make_pair( geometry, world ) );
    }
    else {
        _opaqueObjects[ material ][ primitive ].push_back( std::make_pair( geometry, world ) );
    }
}

void RenderQueue::push( LightPtr const &light )
{
    _lights.push_back( light );
}

void RenderQueue::each( MaterialMap const &objects, std::function< void( MaterialPtr const &, PrimitiveMap const & ) > callback )
{
    auto os = objects;
	for ( auto it : os ) {
		callback( it.first, it.second );
	}
}

void RenderQueue::each( std::function< void ( const LightPtr &, int ) > callback )
{
    auto lights = _lights;
    int i = 0;
    for ( auto l : lights ) {
        callback( l, i++ );
    }
}
