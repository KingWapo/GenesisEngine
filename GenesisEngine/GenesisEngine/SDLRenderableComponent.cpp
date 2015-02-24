#include "SDLRenderableComponent.h"
#include "SDL\SDL_image.h"

#include "Vector2.h"

//const char *RenderableComponent::g_Name = "SDLRenderableComponent";

SDLRenderableComponent::SDLRenderableComponent() : RenderableComponent()
{
	/* No, let the parent initialize these (less code duplication)
	m_spriteFileLocation = "";
	m_location = Vector2(0, 0);
	m_size = Vector2(0, 0);
	m_cell = Vector2(0, 0);
	*/

	m_renderer = NULL;
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
	m_renderer = p_window->getRenderer();
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
	SDL_DestroyTexture(m_sprite);
	//SDL_Quit();
}

bool SDLRenderableComponent::vInit()
{
	GCC_ASSERT(m_pOwner.get() != NULL);

	Actor* l_owner = static_cast<Actor*>(m_pOwner.get());

	m_transform = l_owner->GetComponent<Transform2dComponent>("Transform2dComponent").lock();

	// SDL should not be initialized at the component level.
	// These calls (and subsequent calls to SDL_Quit) should be happening at the application level.

	if (!RenderableComponent::vInit())
	{
		return false;
	}

	//if (SDL_Init(SDL_INIT_VIDEO) < 0)
	//{
	//	printf("SDL Error: %s\n", SDL_GetError()); fflush(stdout);
	//	return false;
	//}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		return false;
	}

	SDL_Surface* imageSurface = IMG_Load(m_spriteFileLocation);
	if (imageSurface == NULL)
	{
		return false;
	}

	//m_sprite = SDL_CreateTextureFromSurface(m_renderer, imageSurface);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	int Mode = GL_RGB;

	if (imageSurface->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, imageSurface->w, imageSurface->h, 0, Mode, GL_UNSIGNED_BYTE, imageSurface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*if (m_sprite == NULL)
	{
		printf("Texture creation failed.\n"); fflush(stdout);
		SDL_FreeSurface(imageSurface);
		return false;
	}*/

	printf("Texture creation and loaded.\n"); fflush(stdout);

	SDL_FreeSurface(imageSurface);
	return true;
}

void SDLRenderableComponent::vPostInit()
{

}

bool SDLRenderableComponent::vUpdate(int deltaMs)
{
	// Reset position
	Vector2 loc = m_transform->GetLocation();
	m_location = Point2D(loc.x, loc.y);

	return false;
}

void SDLRenderableComponent::vOnChanged()
{

}

void SDLRenderableComponent::vDraw()
{
	//printf("In vDraw SDLCoimponent.\n"); fflush(stdout);
//	if (isDrawable())
	{
		glBindTexture(GL_TEXTURE_2D, TextureID);

		glBegin(GL_QUADS);
			glTexCoord2f(0.f, 1.f); glVertex2f(m_location.x(), m_location.y()); //Bottom left
			glTexCoord2f(1.f, 1.f); glVertex2f(m_location.x() + m_size.x(), m_location.y()); //Bottom right
			glTexCoord2f(1.f, 0.f); glVertex2f(m_location.x() + m_size.x(), m_location.y() + m_size.y()); //Top right
			glTexCoord2f(0.f, 0.f); glVertex2f(m_location.x(), m_location.y() + m_size.y()); //Top left
		glEnd();
	}
}
