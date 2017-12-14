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

#ifndef CRIMILD_CORE_BEHAVIORS_DECORATORS_DECORATOR_
#define CRIMILD_CORE_BEHAVIORS_DECORATORS_DECORATOR_

#include "Behaviors/Behavior.hpp"

namespace crimild {

	namespace behaviors {

		namespace decorators {

			/**
			   \brief A behavior that alters the way its child works
			*/
			class Decorator : public Behavior {
				CRIMILD_IMPLEMENT_RTTI( crimild::behaviors::decorators:: Decorator )
			protected:
				explicit Decorator( void );

			public:
				virtual ~Decorator( void );
				
				virtual void init( BehaviorContext *context ) override;

				/**
				   \brief Executes the child behavior

				   \remarks By default, the returned state matches the
				   one of the child behavior. If there is no behavior
				   attached to a decorator, the result is FAILURE
				 */
				virtual Behavior::State step( BehaviorContext *context ) override;

				void setBehavior( BehaviorPtr const &behavior ) { _decoratedBehavior = behavior; }
				Behavior *getBehavior( void ) { return crimild::get_ptr( _decoratedBehavior ); }
				
			private:
				BehaviorPtr _decoratedBehavior;
			};

		}

	}
	
}

#endif
