#include "MotionAvoidWalls.hpp"

using namespace crimild;
using namespace crimild::behaviors;
using namespace crimild::behaviors::actions;

MotionAvoidWalls::MotionAvoidWalls( void )
{

}

MotionAvoidWalls::~MotionAvoidWalls( void )
{

}

Behavior::State MotionAvoidWalls::step( BehaviorContext *context )
{
	// TODO
	
	return Behavior::State::SUCCESS;
}

void MotionAvoidWalls::encode( coding::Encoder &encoder )
{
	Behavior::encode( encoder );
}

void MotionAvoidWalls::decode( coding::Decoder &decoder )
{
	Behavior::decode( decoder );
}

