/*
Render:
An instance of this class will be created in the GameInstance class (which replaced MainGame for naming preference).
Then, each time an actor has a renderingcomponent added to them, they can load their image through the render. This
would then add the information (possibly saved in the Sprite.h enum once it's reorganized) to a list in the render.
Then during each phrase it would run through the list and draw them at the correct location. I'm also thinking of
returning a reference to the sprite object back to the render component, so that it would be able to change the
location of the sprite based off of the actor's location. 
*/

#pragma once
#include "Window.h"

#include <list>

class Render
{
public:
	Render();
	~Render();


	// Initialize SDL (or OpenGL). Does this need
	// a reference to the Window open? Saw examples
	// that did and some that didn't. Should the Window
	// actually be created here?
	bool Init(Window p_Window);


	// Run through the list of sprites and draw them
	// based off of their information.
	void Draw();

	// What I want it to do:
	// Create sprite using SDL_Surface, position etc.
	// Everything needed to draw it. Add said sprite
	// to the list of sprites. Return reference to 
	// said sprite so the actor can change the
	// position of it? Plausible? or no?
	bool AddSprite(const char *p_spriteLocation);

	// After a sprite is done being drawn, remove it.
	// Would this be easy? Or even possible? Or is there
	// a better way to handle holding the sprites.
	void RemoveSprite();

private:
	// List of the sprites and the information needed
	// to draw each one. Would be changed to
	// std::list<Sprite *> m_sprites instead in this
	// case.
	std::list<SDL_Surface *> m_sprites;

	// Need an instance of just the screen or something?
	// Saw an example, but not sure what they really needed with this.
	SDL_Surface *m_screen;
};

