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
public:
	Animation();
	Animation(int fs, int fe);
	~Animation();

	//John - getters
	int getFrameStart(){ return frameStart; }
	int getFrameEnd(){ return frameEnd; }

	//John - setters
	void setFrameStart(int fs){ frameStart = fs; }
	void setFrameEnd(int fe){ frameEnd = fe; }
};

