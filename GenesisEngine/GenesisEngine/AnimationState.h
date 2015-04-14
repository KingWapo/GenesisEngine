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
	Animation *animations;			//John - cells in the array will be different directions for animation state
											//0 - left, 1 - right, 2 - up, 3 - down

	int timer = 0;								//the amount of time a frame has been displaying on screen
	int delay;									//the amount of delay between frames in the animation
	int offset = 0;								//offset from the starting frame - used to cycle through frames in an animation
public:
	AnimationState();
	AnimationState(std::string name, int numDirections, int delay);
	~AnimationState();

	std::string getName(){ return stateName; }
	void setName(std::string name){ stateName = name; }

	bool isActive(){ return isStateActive; }
	void setActive(bool val) { isStateActive = val; }

	void setDirectionAnimation(Animation anim, int direction){ animations[direction] = anim; }
	Animation getDirectionAnimation(int direction){ return animations[direction]; }

	int getTimer(){ return timer; }
	int getDelay(){ return delay; }
	int getOffset(){ return offset; }

	void setTimer(int t){ timer = t; }
	void setDelay(int d){ delay = d; }
	void setOffset(int o){ offset = o; }
};

