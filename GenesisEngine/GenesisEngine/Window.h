#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>

enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

class Window
{
public:
	Window();
	~Window();

	int Create(std::string p_WindowName, int p_ScreenWidth, int p_ScreenHeight, unsigned int p_CurrentFlags);

	void SwapBuffer();

	int GetScreenWidth() { return m_ScreenWidth; }
	int GetScreenHeight() { return m_ScreenHeight; }

	SDL_Window* getSurface() { return m_SDLWindow; }
	SDL_Renderer* getRenderer() { return m_SDLRenderer; }

private:
	SDL_Window* m_SDLWindow;
	SDL_Renderer* m_SDLRenderer;
	int m_ScreenWidth, m_ScreenHeight;
};