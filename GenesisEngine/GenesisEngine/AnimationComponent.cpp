#include "AnimationComponent.h"
#include "SDL\SDL_image.h"

#include "Vector2.h"

#include <iostream>

AnimationComponent::AnimationComponent() : RenderableComponent()
{
	totFrames = 80;
	numColumns = 10;

	m_renderer = NULL;
	m_window = NULL;
	m_screen = NULL;
	m_sprite = NULL;

	initVariables();
}

AnimationComponent::AnimationComponent(const char* p_fileLocation, int totalFrames, int numberColumns, Point2DF p_location, Point2DF p_size, Point2DF p_cell, Window* p_window)
	: RenderableComponent(p_fileLocation, p_location, p_size, p_cell){

	totFrames = totalFrames;
	numColumns = numberColumns;	

	m_window = p_window->getSurface();
	m_renderer = p_window->getRenderer();
	m_screen = SDL_GetWindowSurface(m_window);
	m_sprite = NULL;

	initVariables();
}


AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::initVariables(){
	numberRows = totFrames / numColumns;
	currentFrame = 0; // Matt: [0,totalFrames-1]
	frameCol = (currentFrame) % numColumns;
	frameRow = (int)(currentFrame / numColumns);
	frameX = (0.0 + frameCol) / numColumns;
	frameX2 = (1.0 + frameCol) / numColumns;
	frameY = (0.0 + frameRow) / numberRows;
	frameY2 = (1.0 + frameRow) / numberRows;
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

	//John - improve with animation states
	//get direction info from controller

	//check if facing left or right
	if (preLocationX < m_location.x())
		direction = 1;
	else if (preLocationX > m_location.x())
		direction = 0;	
	
	//check if falling
	if (preLocationY > m_location.y() || (preLocationY == m_location.y() && jumping))
		falling = 1;
	else
		falling = 0;

	//check if jumping
	if (preLocationY >= m_location.y())
		jumping = 0;
}

void AnimationComponent::animations(){
	//new code:
	//get direction and animation state
	//check if animation state or direction has changed
	//if yes...
		//cycle through animation list
		//draw animation that matches state and direction
	//if no...
		//continue drawing previous animation

	if (direction) { //right
		if (preLocationY < m_location.y()) {
			if (jumping == 0) {
				jumping = 1;
				jumpTimer = 0;
				jumpOffset = 0;
			}
			if (jumpOffset < rightJumpEnd - rightJumpStart + 1)
				currentFrame = rightJumpStart + jumpOffset;
			else
				currentFrame = rightJumpEnd;
		}
		else if (falling)
			currentFrame = rightFallStart + fallOffset % (rightFallEnd - rightFallStart + 1);
		else if (preLocationX < m_location.x())
			currentFrame = rightMoveStart + moveOffset % (rightMoveEnd - rightMoveStart + 1);
		else
			currentFrame = rightStandStart + standOffset % (rightStandEnd - rightStandStart + 1);
	}
	else { //left
		if (preLocationY < m_location.y()) {
			if (jumping == 0) {
				jumping = 1;
				jumpTimer = 0;
				jumpOffset = 0;
			}
			if (jumpOffset < leftJumpEnd - leftJumpStart + 1)
				currentFrame = leftJumpStart + jumpOffset;
			else
				currentFrame = leftJumpEnd;
		}
		else if (falling)
			currentFrame = leftFallStart + fallOffset % (leftFallEnd - leftFallStart + 1);
		else if (preLocationX > m_location.x())
			currentFrame = leftMoveStart + moveOffset % (leftMoveEnd - leftMoveStart + 1);
		else
			currentFrame = leftStandStart + standOffset % (leftStandEnd - leftStandStart + 1);
	}
}

void AnimationComponent::updateVariables(){
	preLocationX = m_location.x();
	preLocationY = m_location.y();

	frameCol = (currentFrame) % numColumns;
	frameRow = (int)floor(currentFrame / numColumns);
	frameX = (0.0 + frameCol) / numColumns;
	frameX2 = (1.0 + frameCol) / numColumns;
	frameY = (0.0 + frameRow) / numberRows;
	frameY2 = (1.0 + frameRow) / numberRows;

	if (moveTimer > moveDelay) {
		moveOffset++;
		moveTimer = 0;
	}
	if (standTimer > standDelay) {
		standOffset++;
		standTimer = 0;
	}
	if (jumpTimer > jumpDelay) {
		jumpOffset++;
		jumpTimer = 0;
	}
	if (fallTimer > fallDelay) {
		fallOffset++;
		fallTimer = 0;
	}
	moveTimer++;
	standTimer++;
	jumpTimer++;
	fallTimer++;
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


