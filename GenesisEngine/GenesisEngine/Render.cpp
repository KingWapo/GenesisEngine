#include "Render.h"

#include "SDL\SDL.h"

Render::Render()
{
}


Render::~Render()
{
}

bool Render::Init(Window p_Window)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		// Unable to load SDL
		return false;
	}

	atexit(SDL_Quit);
}

void Render::Draw()
{

}

bool Render::AddSprite(const char *p_spriteLocation)
{
	SDL_Surface *temp = NULL;
	//SDL_Surface *optimized = NULL;

	if ((temp = SDL_LoadBMP(p_spriteLocation)) == NULL)
	{
		return false;
	}

	return true;
}

void Render::RemoveSprite()
{

}