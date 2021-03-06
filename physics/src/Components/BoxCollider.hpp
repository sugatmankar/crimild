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

#ifndef CRIMILD_PHYSICS_COMPONENTS_BOX_COLLIDER_
#define CRIMILD_PHYSICS_COMPONENTS_BOX_COLLIDER_

#include "Collider.hpp"

namespace crimild {

	namespace physics {

		class BoxCollider : public Collider {
		public:
			BoxCollider( void );
			BoxCollider( const Vector3f &boxHalfExtents );
			virtual ~BoxCollider( void );

			void setOffset( const Vector3f &offset ) { _offset = offset; }
			const Vector3f &getOffset( void ) const { return _offset; }

			void setHalfExtents( const Vector3f &boxHalfExtents ) { _boxHalfExtents = boxHalfExtents; }
			const Vector3f &getHalfExtents( void ) const { return _boxHalfExtents; }

		private:
			Vector3f _offset;
			Vector3f _boxHalfExtents;

		public:
			virtual SharedPointer< btCollisionShape > generateShape( void ) override;

		public:
			virtual void renderDebugInfo( Renderer *renderer, Camera *camera ) override;
		};
        
	}
	
}

#endif

