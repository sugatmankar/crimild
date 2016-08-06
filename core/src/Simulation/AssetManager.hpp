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

#ifndef CRIMILD_CORE_SIMULATION_ASSET_MANAGER_
#define CRIMILD_CORE_SIMULATION_ASSET_MANAGER_

#include "Foundation/SharedObject.hpp"
#include "Foundation/Macros.hpp"
#include "Foundation/Singleton.hpp"

#include "Visitors/ShallowCopy.hpp"

#include <memory>
#include <map>
#include <string>

namespace crimild {

    class Texture;

    class AssetManager : public NonCopyable, public DynamicSingleton< AssetManager > {
    public:
        static constexpr const char *FONT_DEFAULT = "fonts/default";
        
    public:
        AssetManager( void );
        virtual ~AssetManager( void );

        void set( std::string name, SharedPointer< SharedObject > const &asset, bool isPersistent = false )
        {
            if ( isPersistent ) {
                _persistentAssets[ name ] = asset;
            }
            else {
                _assets[ name ] = asset;
            }
        }
        
        template< class T >
        T *get( std::string name )
        {
            auto &asset = _assets[ name ];
            if ( asset == nullptr ) {
                asset = _persistentAssets[ name ];
            }
            
            return static_cast< T * >( crimild::get_ptr( asset ) );
        }

        template< class T >
        SharedPointer< T > clone( std::string filename )
        {
            auto assetProto = get< T >( filename );
            assert( assetProto != nullptr && ( filename + " does not exist in Asset Manager cache" ).c_str() );
    
            ShallowCopy shallowCopy;
            assetProto->perform( shallowCopy );
            return shallowCopy.getResult< T >();
        }

        void clear( void )
        {
            _assets.clear();
        }

    private:
        std::map< std::string, SharedPointer< SharedObject > > _assets;
        std::map< std::string, SharedPointer< SharedObject > > _persistentAssets;
    };

    template<>
    Texture *AssetManager::get< Texture >( std::string name );

}

#endif

