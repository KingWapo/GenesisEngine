#pragma once
#include "RenderableComponent.h"
#include "Transform2dComponent.h"
#include "Actor.h"
#include "Window.h"

#include "SDL\SDL.h"

class Animation
{
private:
	int frameStart;							//the frame on the spritesheet where the animation starts
	int frameEnd;							//the frame on the spritesheet where the animation ends
	int timer;								//the amount of time to lapse before the animation begins playing
	int delay;								//the amount of delay between frames in the animation
	int offset;								//offset
public:
	Animation();
	Animation(int fs, int fe, int t, int d, int o);
	~Animation();

	//John - getters
	int getFrameStart(){ return frameStart; }
	int getFrameEnd(){ return frameEnd; }
	int getTimer(){ return timer; }
	int getOffset(){ return offset; }

	//John - setters
	void setFrameStart(int fs){ frameStart = fs; }
	void setFrameEnd(int fe){ frameEnd = fe; }
	void setTimer(int t){ timer = t; }
	void setDelay(int d){ delay = d; }
	void setOffset(int o){ offset = o; }

};

