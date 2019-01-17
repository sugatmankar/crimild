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

#ifndef CRIMILD_CORE_RENDERING_PROGRAMS_PHONG_DEFERRED_LIGHTING_
#define CRIMILD_CORE_RENDERING_PROGRAMS_PHONG_DEFERRED_LIGHTING_

#include "Rendering/ShaderProgram.hpp"
#include "Rendering/ShaderUniformImpl.hpp"

namespace crimild {

	class PhongDeferredLightingShaderProgram : public ShaderProgram {
	public:
		PhongDeferredLightingShaderProgram( void );
		virtual ~PhongDeferredLightingShaderProgram( void );

		void bindModelMatrix( const Matrix4f &value ) { _modelMatrix->setValue( value ); }
		void bindViewMatrix( const Matrix4f &value ) { _viewMatrix->setValue( value ); }
		void bindProjMatrix( const Matrix4f &value ) { _projMatrix->setValue( value ); }
		void bindLightAmbientTexture( Texture *value ) { _lightAmbientTexture->setValue( value ); }
		void bindLightDiffuseTexture( Texture *value ) { _lightDiffuseTexture->setValue( value ); }
		void bindLightSpecularTexture( Texture *value ) { _lightSpecularTexture->setValue( value ); }
		void bindMaterialAmbient( const RGBAColorf &value ) { _materialAmbient->setValue( value ); }
		void bindMaterialDiffuse( const RGBAColorf &value ) { _materialDiffuse->setValue( value ); }
		void bindMaterialSpecular( const RGBAColorf &value ) { _materialSpecular->setValue( value ); }
		void bindMaterialColorMap( Texture *value ) { _materialColorMap->setValue( value ); }
		void bindMaterialSpecularMap( Texture *value ) { _materialSpecularMap->setValue( value ); }
		void bindScreenSize( const Vector2f &value ) { _screenSize->setValue( value ); }
		
	private:
		void createVertexShader( void );
		void createFragmentShader( void );

	private:
		SharedPointer< Matrix4fUniform > _modelMatrix;
		SharedPointer< Matrix4fUniform > _viewMatrix;
		SharedPointer< Matrix4fUniform > _projMatrix;
		SharedPointer< TextureUniform > _lightAmbientTexture;
		SharedPointer< TextureUniform > _lightDiffuseTexture;
		SharedPointer< TextureUniform > _lightSpecularTexture;
		SharedPointer< RGBAColorfUniform > _materialAmbient;
		SharedPointer< RGBAColorfUniform > _materialDiffuse;
		SharedPointer< RGBAColorfUniform > _materialSpecular;
		SharedPointer< TextureUniform > _materialColorMap;
		SharedPointer< TextureUniform > _materialSpecularMap;
		SharedPointer< Vector2fUniform > _screenSize;		
	};

}

#endif
