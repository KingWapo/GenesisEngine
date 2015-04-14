#include "Animation.h"


Animation::Animation()
{
	frameStart = NULL;
	frameEnd = NULL;
	timer = NULL;
	delay = NULL;
	offset = NULL;
}

Animation::Animation(int fs, int fe, int t, int d, int o)
{
	frameStart = fs;
	frameEnd = fe;
	timer = t;
	delay = d;
	offset = o;
}

Animation::~Animation()
{
}
