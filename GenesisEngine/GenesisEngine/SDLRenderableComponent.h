#pragma once
#include "RenderableComponent.h"
#include "Window.h"

#include "SDL\SDL.h"

class SDLRenderableComponent : public RenderableComponent
{
private:
	SDL_Surface* m_sprite;
	SDL_Surface* m_screen;
	SDL_Window* m_window;

	SDL_Rect m_source;
	SDL_Rect m_position;

public:
	SDLRenderableComponent();
	SDLRenderableComponent(const char* p_fileLocation, Vector2 p_location, Vector2 p_size, Vector2 p_cell, Window* p_window);
	~SDLRenderableComponent();

	virtual bool vInit(void) override;
	virtual void vPostInit(void) override;
	virtual void vUpdate(int deltaMs) override;
	virtual void vOnChanged(void) override;

	virtual void vDraw(void) override;

	void SetWindowSurface(Window* p_window) { m_window = p_window->getSurface(); m_screen = SDL_GetWindowSurface(m_window); }
};

