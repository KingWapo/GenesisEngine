#pragma once
#include "RenderableComponent.h"
#include "Transform2dComponent.h"
#include "Actor.h"
#include "String.h"
#include "Window.h"
#include "Animation.h"

#include "SDL\SDL.h"

class AnimationState
{
	std::string stateName;
	bool isStateActive = false;
	Animation animations[] = {};			//John - cells in the array will be different directions for animation state
											//0 - left, 1 - right, 2 - up, 3 - down
public:
	AnimationState();
	AnimationState(std::string name);
	~AnimationState();

	bool isActive(){ return isStateActive; }
	void setActive(bool val) { isStateActive = val; }

	void setDirectionAnimation(Animation anim, int direction){ animations[direction] = anim; }
	Animation getDirectionAnimation(int direction){ return animations[direction]; }
};

