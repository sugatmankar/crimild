/*
 * Copyright (c) 2002-present, H. Hernan Saez
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

#ifndef CRIMILD_RENDERING_SHADER_GRAPH_NODES_PHONG_FRAGMENT_MASTER_
#define CRIMILD_RENDERING_SHADER_GRAPH_NODES_PHONG_FRAGMENT_MASTER_

#include "Rendering/ShaderGraph/Expression.hpp"

namespace crimild {

	namespace shadergraph {

		class Variable;

		class PhongFragmentMaster : public Expression {
			CRIMILD_IMPLEMENT_RTTI( crimild::shadergraph::PhongFragmentMaster )
			
		public:
			PhongFragmentMaster( ShaderGraph *graph, crimild::Size maxLights = 4 );
			virtual ~PhongFragmentMaster( void );

			crimild::Size getMaxLights( void ) const { return _maxLights; }

			void setTextureCoords( Variable *var ) { _textureCoords = var; }
			Variable *getTextureCoords( void ) { return _textureCoords; }

			void setWorldNormal( Variable *var ) { _worldNormal = var; }
			Variable *getWorldNormal( void ) { return _worldNormal; }
			
			void setWorldEye( Variable *var ) { _worldEye = var; }
			Variable *getWorldEye( void ) { return _worldEye; }
			
			void setWorldPosition( Variable *var ) { _worldPosition = var; }
			Variable *getWorldPosition( void ) { return _worldPosition; }
			
			void setAmbient( Variable *var ) { _ambient = var; }
			Variable *getAmbient( void ) { return _ambient; }
			
			void setDiffuse( Variable *var ) { _diffuse = var; }
			Variable *getDiffuse( void ) { return _diffuse; }
			
			void setSpecular( Variable *var ) { _specular = var; }
			Variable *getSpecular( void ) { return _specular; }
			
			void setShininess( Variable *var ) { _shininess = var; }
			Variable *getShininess( void ) { return _shininess; }
			
			void setAlpha( Variable *var ) { _alpha = var; }
			Variable *getAlpha( void ) { return _alpha; }
			
			void setAlphaClipThreshold( Variable *var ) { _alphaClipThreshold = var; }
			Variable *getAlphaClipThreshold( void ) { return _alphaClipThreshold; }
			
		private:
			crimild::Size _maxLights;

			Variable *_textureCoords = nullptr;
			Variable *_worldNormal = nullptr;
			Variable *_worldEye = nullptr;
			Variable *_worldPosition = nullptr;
			Variable *_ambient = nullptr;
			Variable *_diffuse = nullptr;
			Variable *_specular = nullptr;
			Variable *_shininess = nullptr;
			Variable *_alpha = nullptr;
			Variable *_alphaClipThreshold = nullptr;
			
		public:
			virtual void setup( ShaderGraph *graph ) override;
		};
		
	}

}

#endif

