#include "SDLRenderableComponent.h"
#include "SDL\SDL_image.h"

#include "Vector2.h"

#include <iostream>

//const char *RenderableComponent::g_Name = "SDLRenderableComponent";

//Matt - dumping a bunch of sprite sheet animation crap here for now
/*
int totalFrames = 80;
int numberColumns = 10;
int numberRows = totalFrames / numberColumns;
int currentFrame = 0; // [0,totalFrames-1]
int frameCol = (currentFrame) % numberColumns;
int frameRow = ceil(currentFrame / numberColumns);
double frameX = (0.0 + frameCol) / numberColumns;
double frameX2 = (1.0 + frameCol) / numberColumns;
double frameY = (0.0 + frameRow) / numberRows;
double frameY2 = (1.0 + frameRow) / numberRows;

int rightStandStart = 30;
int rightStandEnd = 32;
int rightMoveStart = 70;
int rightMoveEnd = 79;
int rightJumpStart = 72;
int rightJumpEnd = 72;

int leftStandStart = 10;
int leftStandEnd = 12;
int leftMoveStart = 50;
int leftMoveEnd = 59;
int leftJumpStart = 52;
int leftJumpEnd = 52;

float preLocationX;
float preLocationY;

boolean left = 0;
boolean right = 1;

int moveTimer = 0;
int standTimer = 0;
int moveDelay = 7;
int standDelay = 7;
int offset = 0;
*/

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

	/*
	m_source.x = m_cell.x();
	m_source.y = m_cell.y();
	m_source.w = m_size.x();
	m_source.h = m_size.y();

	m_position.x = m_location.x();
	m_position.y = m_location.y();
	m_position.w = m_size.x();
	m_position.h = m_size.y();
	*/
}


SDLRenderableComponent::SDLRenderableComponent(const char* p_fileLocation, Point2DF p_location, Point2DF p_size, Point2DF p_cell, Window* p_window)
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

	/*
	m_source.x = m_cell.x();
	m_source.y = m_cell.y();
	m_source.w = m_size.x();
	m_source.h = m_size.y();

	m_position.x = m_location.x();
	m_position.y = m_location.y();
	m_position.w = m_size.x();
	m_position.h = m_size.y();
	*/
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

	m_transform = l_owner->GetComponent<Transform2dComponent>("Transform2dComponent");

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

	//John - replacing generation of SDL Texture to generation of openGL texture

	//John - conversion of SDL surface to openGL texture
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

	//John - debug stating texture is created and loaded
	printf("Texture creation and loaded.\n"); fflush(stdout);

	//John - free sdl surface
	SDL_FreeSurface(imageSurface);
	return true;
}

void SDLRenderableComponent::vPostInit()
{

}

bool SDLRenderableComponent::vUpdate(int deltaMs)
{
	// Reset position
	Vector2 loc = m_transform->GetTranslation();
	m_location = Point2DF(loc.x, loc.y);

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
		//John - binds texture to rect
		glBindTexture(GL_TEXTURE_2D, TextureID);

		//Matt - dumping a bunch of sprite sheet animation crap here for now
		/*
		//Matt - Check direction
		if (preLocationX < m_location.x()) {
			right = 1;
			left = 0;
		}
		else if (preLocationX > m_location.x()) {
			left = 1;
			right = 0;
		}

		//Matt - Animations
		if (right) {
			if (preLocationY < m_location.y() || preLocationY > m_location.y()) {
				currentFrame = rightJumpStart;
			}
			else if (preLocationX < m_location.x())	{
				if (moveTimer > moveDelay)
				currentFrame = rightMoveStart + offset % (rightMoveEnd - rightMoveStart + 1);
			}
			else {
				if (standTimer > standDelay)
					currentFrame = rightStandStart + offset % (rightStandEnd - rightStandStart + 1);
			}
		}
		else if (left) {
			if (preLocationY < m_location.y() || preLocationY > m_location.y()) {
				currentFrame = leftJumpStart;
			}
			else if (preLocationX > m_location.x())	{
				if (moveTimer > moveDelay)
					currentFrame = leftMoveStart + offset % (leftMoveEnd - leftMoveStart + 1);
			}
			else {
				if (standTimer > standDelay)
					currentFrame = leftStandStart + offset % (leftStandEnd - leftStandStart + 1);
			}
		}

		//Matt - Update variables
		preLocationX = m_location.x();
		preLocationY = m_location.y();

		frameCol = (currentFrame) % numberColumns;
		frameRow = floor(currentFrame / numberColumns);
		frameX = (0.0 + frameCol) / numberColumns;
		frameX2 = (1.0 + frameCol) / numberColumns;
		frameY = (0.0 + frameRow) / numberRows;
		frameY2 = (1.0 + frameRow) / numberRows;
		if (moveTimer > moveDelay) {
			offset++;
			moveTimer = 0;
		}
		if (standTimer > standDelay) {
			offset++;
			standTimer = 0;
		}
		moveTimer++;
		standTimer++;
		
		glBegin(GL_QUADS);
		glTexCoord2f(frameX, frameY2); glVertex2f(m_location.x(), m_location.y()); //Bottom left
		glTexCoord2f(frameX2, frameY2); glVertex2f(m_location.x() + m_size.x(), m_location.y()); //Bottom right
		glTexCoord2f(frameX2, frameY); glVertex2f(m_location.x() + m_size.x(), m_location.y() + m_size.y()); //Top right
		glTexCoord2f(frameX, frameY); glVertex2f(m_location.x(), m_location.y() + m_size.y()); //Top left
		glEnd();
 */
		//John - draws rect
		glBegin(GL_QUADS);
			glTexCoord2f(0.f, 1.f); glVertex2f(m_location.x(), m_location.y()); //Bottom left
			glTexCoord2f(1.f, 1.f); glVertex2f(m_location.x() + m_size.x(), m_location.y()); //Bottom right
			glTexCoord2f(1.f, 0.f); glVertex2f(m_location.x() + m_size.x(), m_location.y() + m_size.y()); //Top right
			glTexCoord2f(0.f, 0.f); glVertex2f(m_location.x(), m_location.y() + m_size.y()); //Top left
		glEnd();
	}
}
