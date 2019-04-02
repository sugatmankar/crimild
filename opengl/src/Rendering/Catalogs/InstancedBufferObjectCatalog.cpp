/*
 * Copyright (c) 2002 - present, H. Hernan Saez
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

#include "InstancedBufferObjectCatalog.hpp"

#include "Rendering/OpenGLUtils.hpp"

#include <Rendering/ShaderProgram.hpp>
#include <Rendering/InstancedBufferObject.hpp>

using namespace crimild;
using namespace crimild::opengl;

InstancedBufferObjectCatalog::InstancedBufferObjectCatalog( void )
{

}

InstancedBufferObjectCatalog::~InstancedBufferObjectCatalog( void )
{

}

int InstancedBufferObjectCatalog::getNextResourceId( InstancedBufferObject * )
{
    CRIMILD_CHECK_GL_ERRORS_BEFORE_CURRENT_FUNCTION;
    
	GLuint bufferId;
    glGenBuffers( 1, &bufferId );
    
    CRIMILD_CHECK_GL_ERRORS_AFTER_CURRENT_FUNCTION;

    return bufferId;
}

void InstancedBufferObjectCatalog::bind( InstancedBufferObject *buffer )
{
	if ( buffer == nullptr ) return;

	CRIMILD_CHECK_GL_ERRORS_BEFORE_CURRENT_FUNCTION;

	if ( buffer->getCatalog() == nullptr ) {
		Catalog< InstancedBufferObject >::bind( buffer );
    }

    GLuint bufferId = buffer->getCatalogId();

	glBindBuffer( GL_ARRAY_BUFFER, bufferId );

	auto vec4Size = 4 * sizeof( crimild::Real32 );
	auto layoutLocation = VertexFormat::LayoutLocation::INSTANCED_ATTRIBUTE;

	// TODO: This assumes we're using a matrix, which is not always the case
	for ( crimild::Size i = 0; i < 4; i++ ) {
		glEnableVertexAttribArray( layoutLocation + i );
		glVertexAttribPointer(
			layoutLocation + i,
			4,
			GL_FLOAT,
			GL_FALSE,
			4 * vec4Size,
			( void * ) ( i * vec4Size )
		);
		glVertexAttribDivisor( layoutLocation + i, 1 );
	}

	/*
    glBindBuffer( GL_ARRAY_BUFFER, bufferId );
    float *baseOffset = 0;

    const InstancedFormat &format = buffer->getInstancedFormat();

	if ( format.hasPositions() ) {
		glEnableInstancedAttribArray( InstancedFormat::LayoutLocation::POSITION );
		glInstancedAttribPointer(
			InstancedFormat::LayoutLocation::POSITION,
			format.getPositionComponents(),
			GL_FLOAT,
			GL_FALSE,
			format.getInstancedSizeInBytes(),
			( const GLvoid * )( baseOffset + format.getPositionsOffset() ) );
	}

	if ( format.hasNormals() ) {
		glEnableInstancedAttribArray( InstancedFormat::LayoutLocation::NORMAL );
		glVertexAttribPointer(
			VertexFormat::LayoutLocation::NORMAL,
			format.getNormalComponents(),
			GL_FLOAT,
			GL_FALSE,
			format.getVertexSizeInBytes(),
			( const GLvoid * )( baseOffset + format.getNormalsOffset() ) );
	}

	if ( format.hasTangents() ) {
		glEnableVertexAttribArray( VertexFormat::LayoutLocation::TANGENT );
		glVertexAttribPointer(
			VertexFormat::LayoutLocation::TANGENT,
			format.getTangentComponents(),
			GL_FLOAT,
			GL_FALSE,
			format.getVertexSizeInBytes(),
			( const GLvoid * )( baseOffset + format.getTangentsOffset() ) );
    }

	if ( format.hasColors() ) {
		glEnableVertexAttribArray( VertexFormat::LayoutLocation::COLOR );
		glVertexAttribPointer(
			VertexFormat::LayoutLocation::COLOR,
			format.getColorComponents(),
			GL_FLOAT,
			GL_FALSE,
			format.getVertexSizeInBytes(),
			( const GLvoid * )( baseOffset + format.getColorsOffset() ) );
    }

	if ( format.hasTextureCoords() ) {
		glEnableVertexAttribArray( VertexFormat::LayoutLocation::TEXTURE_COORD );
		glVertexAttribPointer(
			VertexFormat::LayoutLocation::TEXTURE_COORD,
			format.getTextureCoordComponents(),
			GL_FLOAT,
			GL_FALSE,
			format.getVertexSizeInBytes(),
			( const GLvoid * )( baseOffset + format.getTextureCoordsOffset() ) );
	}

	if ( format.hasBoneIds() ) {
		glEnableVertexAttribArray( VertexFormat::LayoutLocation::BONE_ID );
		glVertexAttribPointer(
			VertexFormat::LayoutLocation::BONE_ID,
			format.getBoneIdComponents(),
			GL_FLOAT,
			GL_FALSE,
			format.getVertexSizeInBytes(),
			( const GLvoid * )( baseOffset + format.getBoneIdsOffset() ) );
    }

	if ( format.hasBoneWeights() ) {
		glEnableVertexAttribArray( VertexFormat::LayoutLocation::BONE_WEIGHT );
		glVertexAttribPointer(
			VertexFormat::LayoutLocation::BONE_WEIGHT,
			format.getBoneWeightComponents(),
			GL_FLOAT,
			GL_FALSE,
			format.getVertexSizeInBytes(),
			( const GLvoid * )( baseOffset + format.getBoneWeightsOffset() ) );
	}
	*/

    CRIMILD_CHECK_GL_ERRORS_AFTER_CURRENT_FUNCTION;
}

void InstancedBufferObjectCatalog::unbind( InstancedBufferObject *buffer )
{
	if ( buffer == nullptr ) return;

	CRIMILD_CHECK_GL_ERRORS_BEFORE_CURRENT_FUNCTION;

	auto layoutLocation = VertexFormat::LayoutLocation::INSTANCED_ATTRIBUTE;

	// TODO: This assumes we're using a matrix, which is not always the case
	for ( crimild::Size i = 0; i < 4; i++ ) {
		glDisableVertexAttribArray( layoutLocation + i );
	}
	/*
	
    const VertexFormat &format = buffer->getVertexFormat();

	if ( format.hasPositions() ) glDisableVertexAttribArray( VertexFormat::LayoutLocation::POSITION );
	if ( format.hasNormals() ) glDisableVertexAttribArray( VertexFormat::LayoutLocation::NORMAL );
	if ( format.hasTangents() ) glDisableVertexAttribArray( VertexFormat::LayoutLocation::TANGENT );
	if ( format.hasColors() ) glDisableVertexAttribArray( VertexFormat::LayoutLocation::COLOR );
	if ( format.hasTextureCoords() ) glDisableVertexAttribArray( VertexFormat::LayoutLocation::TEXTURE_COORD );
	if ( format.hasBoneIds() ) glDisableVertexAttribArray( VertexFormat::LayoutLocation::BONE_ID );
	if ( format.hasBoneWeights() ) glDisableVertexAttribArray( VertexFormat::LayoutLocation::BONE_WEIGHT );
	*/

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    
	Catalog< InstancedBufferObject >::unbind( buffer );

    CRIMILD_CHECK_GL_ERRORS_AFTER_CURRENT_FUNCTION;
}

void InstancedBufferObjectCatalog::load( InstancedBufferObject *buffer )
{
	if ( buffer == nullptr ) return;
	
	CRIMILD_CHECK_GL_ERRORS_BEFORE_CURRENT_FUNCTION;

	Catalog< InstancedBufferObject >::load( buffer );

	GLuint bufferId = buffer->getCatalogId();

    glBindBuffer( GL_ARRAY_BUFFER, bufferId );
    glBufferData( GL_ARRAY_BUFFER, buffer->getSizeInBytes(), buffer->getData(), GL_STATIC_DRAW );

    CRIMILD_CHECK_GL_ERRORS_AFTER_CURRENT_FUNCTION;
}

void InstancedBufferObjectCatalog::unload( InstancedBufferObject *buffer )
{
	if ( buffer == nullptr ) return;
	
    CRIMILD_CHECK_GL_ERRORS_BEFORE_CURRENT_FUNCTION;
    
    if ( buffer->getCatalogId() > 0 ) {
      	_unusedBufferIds.push_back( buffer->getCatalogId() );
    }

    Catalog< InstancedBufferObject >::unload( buffer );
    
    CRIMILD_CHECK_GL_ERRORS_AFTER_CURRENT_FUNCTION;
}

void InstancedBufferObjectCatalog::cleanup( void )
{
    CRIMILD_CHECK_GL_ERRORS_BEFORE_CURRENT_FUNCTION;
    
    for ( auto id : _unusedBufferIds ) {
        GLuint bufferId = id;
        glDeleteBuffers( 1, &bufferId );
    }
    
    _unusedBufferIds.clear();
    
    CRIMILD_CHECK_GL_ERRORS_AFTER_CURRENT_FUNCTION;
}

