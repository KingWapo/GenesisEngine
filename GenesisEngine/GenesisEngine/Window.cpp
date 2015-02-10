#include "Window.h"
#include "Errors.h"

Window::Window()
{
}


Window::~Window()
{
}

int Window::Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;

	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & INVISIBLE) {
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (currentFlags & FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	m_SDLWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

	if (m_SDLWindow == nullptr) {
		fatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(m_SDLWindow);
	if (glContext == nullptr) {
		fatalError("SDL_GL Context could not be created!");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}

	//Check the OpenGL version
	std::printf("***    OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	//Set VSYNC
	SDL_GL_SetSwapInterval(1);

	// Enable alpha blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

void Window::SwapBuffer() {
	SDL_GL_SwapWindow(m_SDLWindow);
}