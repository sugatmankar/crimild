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

#ifndef CRIMILD_GL3_RENDERING_IMAGE_EFFECT_VIGNETTE_
#define CRIMILD_GL3_RENDERING_IMAGE_EFFECT_VIGNETTE_

#include <Rendering/ImageEffects/ImageEffect.hpp>
#include <Rendering/ShaderUniformImpl.hpp>

namespace crimild {
    
    class ShaderProgram;
    
    namespace opengl {
        
        class VignetteImageEffect : public ImageEffect {
        public:
            VignetteImageEffect( void );
            virtual ~VignetteImageEffect( void );
            
            virtual void compute( crimild::Renderer *renderer, Camera *camera ) override;
            virtual void apply( crimild::Renderer *renderer, crimild::Camera *camera ) override;

            ShaderProgram *getProgram( void ) { return crimild::get_ptr( _program ); }
            
            float getInnerCutoff( void ) { return _innerCutoff->getValue(); }
            void setInnerCutoff( float value ) { _innerCutoff->setValue( value ); }
            
            float getOuterCutoff( void ) { return _outerCutoff->getValue(); }
            void setOuterCutoff( float value ) { _outerCutoff->setValue( value ); }
            
        private:
            SharedPointer< ShaderProgram > _program;
            SharedPointer< FloatUniform > _innerCutoff;
            SharedPointer< FloatUniform > _outerCutoff;
        };
        
    }
    
}

#endif

