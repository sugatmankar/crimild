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

#ifndef CRIMILD_NAVIGATION_CELL_EDGE_
#define CRIMILD_NAVIGATION_CELL_EDGE_

#include "Foundation/Memory.hpp"
#include "Foundation/SharedObject.hpp"
#include "Foundation/RTTI.hpp"
#include "Coding/Codable.hpp"
#include "Streaming/Stream.hpp"

#include "Mathematics/LineSegment.hpp"

namespace crimild {

	namespace navigation {

		class NavigationCell;

        class NavigationCellEdge : public coding::Codable, public StreamObject {
			CRIMILD_IMPLEMENT_RTTI( crimild::navigation::NavigationCellEdge )

		public:
			NavigationCellEdge( const LineSegment3f &line );
			virtual ~NavigationCellEdge( void );

			inline LineSegment3f &getLine( void ) { return _line; }
			inline const LineSegment3f &getLine( void ) const { return _line; }

			inline NavigationCell *getNeighbor( void ) { return _neighbor; }
			void setNeighbor( NavigationCell *neighbor ) { _neighbor = neighbor; }

			LineSegment3f projectPath( const LineSegment3f &path ) const;

		private:
			LineSegment3f _line;
			NavigationCell *_neighbor = nullptr;
		};

		using NavigationCellEdgePtr = SharedPointer< NavigationCellEdge >;

	}

}

#endif

