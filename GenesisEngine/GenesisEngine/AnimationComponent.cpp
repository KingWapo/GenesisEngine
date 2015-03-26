#include "AnimationComponent.h"
#include "SDL\SDL_image.h"

#include "Vector2.h"

#include <iostream>

AnimationComponent::AnimationComponent() : RenderableComponent()
{
	m_renderer = NULL;
	m_window = NULL;
	m_screen = NULL;
	m_sprite = NULL;
}

AnimationComponent::AnimationComponent(const char* p_fileLocation, Point2DF p_location, Point2DF p_size, Point2DF p_cell, Window* p_window)
	: RenderableComponent(p_fileLocation, p_location, p_size, p_cell){

	m_window = p_window->getSurface();
	m_renderer = p_window->getRenderer();
	m_screen = SDL_GetWindowSurface(m_window);
	m_sprite = NULL;
}


AnimationComponent::~AnimationComponent()
{
}

bool AnimationComponent::vInit(){
	GCC_ASSERT(m_pOwner.use_count() != 0);

	StrongActorPtr l_ownerPtr = m_pOwner.lock();
	Actor* l_owner = static_cast<Actor*>(l_ownerPtr.get());

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

void AnimationComponent::vPostInit(){

}

bool AnimationComponent::vUpdate(int deltaMs){
	Vector2 loc = m_transform->GetTranslation();
	m_location = Point2DF(loc.x, loc.y);

	return false;
}

void AnimationComponent::vOnChanged(){

}

void AnimationComponent::checkDirection(){
	if (preLocationX < m_location.x()) {
		right = 1;
		left = 0;
	}
	else if (preLocationX > m_location.x()) {
		left = 1;
		right = 0;
	}
}

void AnimationComponent::animations(){
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
}

void AnimationComponent::updateVariables(){
	preLocationX = m_location.x();
	preLocationY = m_location.y();

	frameCol = (currentFrame) % numberColumns;
	frameRow = (int)floor(currentFrame / numberColumns);
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
}

void AnimationComponent::vDraw(){
	checkDirection();
	animations();
	updateVariables();

	glBindTexture(GL_TEXTURE_2D, TextureID);

	glBegin(GL_QUADS);
	glTexCoord2f(frameX, frameY2); glVertex2f(m_location.x(), m_location.y()); //Bottom left
	glTexCoord2f(frameX2, frameY2); glVertex2f(m_location.x() + m_size.x(), m_location.y()); //Bottom right
	glTexCoord2f(frameX2, frameY); glVertex2f(m_location.x() + m_size.x(), m_location.y() + m_size.y()); //Top right
	glTexCoord2f(frameX, frameY); glVertex2f(m_location.x(), m_location.y() + m_size.y()); //Top left
	glEnd();
}


