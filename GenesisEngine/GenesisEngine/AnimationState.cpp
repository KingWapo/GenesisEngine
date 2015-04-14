#include "AnimationState.h"


AnimationState::AnimationState()
{
	stateName = "";
	animations = new Animation[1];
	delay = NULL;
}

AnimationState::AnimationState(std::string name, int numDirections, int d)
{
	stateName = name;
	animations = new Animation[numDirections];
	delay = d;
}


AnimationState::~AnimationState()
{
}
