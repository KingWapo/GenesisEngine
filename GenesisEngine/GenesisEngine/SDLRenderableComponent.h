#pragma once
#include "RenderableComponent.h"
#include "Window.h"

#include "SDL\SDL.h"

class SDLRenderableComponent : public RenderableComponent
{
private:
	SDL_Texture* m_sprite;
	SDL_Surface* m_screen;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	SDL_Rect m_source;
	SDL_Rect m_position;

public:
	SDLRenderableComponent();
	SDLRenderableComponent(const char* p_fileLocation, Point2D p_location, Point2D p_size, Point2D p_cell, Window* p_window);
	~SDLRenderableComponent();

	virtual bool vInit(void) override;
	virtual void vPostInit(void) override;
	virtual bool vUpdate(int deltaMs) override;
	virtual void vOnChanged(void) override;

	virtual void vDraw(void) override;

	void SetWindowSurface(Window* p_window) { m_window = p_window->getSurface(); m_screen = SDL_GetWindowSurface(m_window); }
};
