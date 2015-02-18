#include "SDLRenderableComponent.h"
#include "SDL\SDL_image.h"

//const char *RenderableComponent::g_Name = "SDLRenderableComponent";

SDLRenderableComponent::SDLRenderableComponent() : RenderableComponent()
{
	/* No, let the parent initialize these (less code duplication)
	m_spriteFileLocation = "";
	m_location = Vector2(0, 0);
	m_size = Vector2(0, 0);
	m_cell = Vector2(0, 0);
	*/

	m_window = NULL;
	m_screen = NULL;
	m_sprite = NULL;

	m_source.x = m_cell.x();
	m_source.y = m_cell.y();
	m_source.w = m_size.x();
	m_source.h = m_size.y();

	m_position.x = m_location.x();
	m_position.y = m_location.y();
	m_position.w = m_size.x();
	m_position.h = m_size.y();
}

SDLRenderableComponent::SDLRenderableComponent(const char* p_fileLocation, Point2D p_location, Point2D p_size, Point2D p_cell, Window* p_window)
	: RenderableComponent(p_fileLocation, p_location, p_size, p_cell)
{
	/* Ditto to above
	m_spriteFileLocation = p_fileLocation;
	m_location = p_location;
	m_size = p_size;
	m_cell = p_cell;
	*/

	m_window = p_window->getSurface();
	m_screen = SDL_GetWindowSurface(m_window);
	m_sprite = NULL;

	m_source.x = m_cell.x();
	m_source.y = m_cell.y();
	m_source.w = m_size.x();
	m_source.h = m_size.y();

	m_position.x = m_location.x();
	m_position.y = m_location.y();
	m_position.w = m_size.x();
	m_position.h = m_size.y();
}

SDLRenderableComponent::~SDLRenderableComponent()
{
	SDL_FreeSurface(m_sprite);
	//SDL_Quit();
}

bool SDLRenderableComponent::vInit()
{
	// SDL should not be initialized at the component level.
	// These calls (and subsequent calls to SDL_Quit) should be happening at the application level.

	if (!RenderableComponent::vInit())
	{
		return false;
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Quit();
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		SDL_Quit();
		return false;
	}

	m_sprite = IMG_Load(m_spriteFileLocation);
	if (m_sprite == NULL)
	{
		SDL_Quit();
		return false;
	}
	
	return true;
}

void SDLRenderableComponent::vPostInit()
{

}

void SDLRenderableComponent::vUpdate(int deltaMs)
{
	// Reset position
}

void SDLRenderableComponent::vOnChanged()
{

}

void SDLRenderableComponent::vDraw()
{
	if (isDrawable())
	{
		SDL_BlitSurface(m_sprite, &m_source, m_screen, &m_position);
	}
}