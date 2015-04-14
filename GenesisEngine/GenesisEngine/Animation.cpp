#include "Animation.h"


Animation::Animation()
{
	frameStart = NULL;
	frameEnd = NULL;
}

Animation::Animation(int fs, int fe)
{
	frameStart = fs;
	frameEnd = fe;
}

Animation::~Animation()
{
}
