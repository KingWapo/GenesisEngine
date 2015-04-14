#include "AnimationComponent.h"
#include "SDL\SDL_image.h"

#include "Vector2.h"

#include <iostream>

const char *AnimationComponent::g_Name = "AnimationComponent";

AnimationComponent::AnimationComponent() : RenderableComponent()
{
	totFrames = NULL;
	numColumns = NULL;

	m_renderer = NULL;
	m_window = NULL;
	m_screen = NULL;
	m_sprite = NULL;

	numberRows = NULL;
	currentFrame = 0; // Matt: [0,totalFrames-1]

	updateVariables();
}

AnimationComponent::AnimationComponent(const char* p_fileLocation, int totalFrames, int numberColumns, Point2DF p_location, Point2DF p_size, Point2DF p_cell, Window* p_window)
	: RenderableComponent(p_fileLocation, p_location, p_size, p_cell){

	totFrames = totalFrames;
	numColumns = numberColumns;	

	m_window = p_window->getSurface();
	m_renderer = p_window->getRenderer();
	m_screen = SDL_GetWindowSurface(m_window);
	m_sprite = NULL;

	numberRows = totFrames / numColumns;
	currentFrame = 0; // Matt: [0,totalFrames-1]

	updateVariables();
}


AnimationComponent::~AnimationComponent()
{
}

bool AnimationComponent::vInit(){
	GCC_ASSERT(m_pOwner.use_count() != 0);

	StrongActorPtr l_ownerPtr = m_pOwner.lock();
	Actor* l_owner = static_cast<Actor*>(l_ownerPtr.get());

	m_transform = l_owner->GetComponent<Transform2dComponent>("Transform2dComponent");

	if (!RenderableComponent::vInit())
	{
		return false;
	}

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

void AnimationComponent::vDraw(){
	animate();

	glBindTexture(GL_TEXTURE_2D, TextureID);

	glBegin(GL_QUADS);
	glTexCoord2f(frameX, frameY2); glVertex2f(m_location.x(), m_location.y()); //Bottom left
	glTexCoord2f(frameX2, frameY2); glVertex2f(m_location.x() + m_size.x(), m_location.y()); //Bottom right
	glTexCoord2f(frameX2, frameY); glVertex2f(m_location.x() + m_size.x(), m_location.y() + m_size.y()); //Top right
	glTexCoord2f(frameX, frameY); glVertex2f(m_location.x(), m_location.y() + m_size.y()); //Top left
	glEnd();
}

void AnimationComponent::updateVariables(){
	frameCol = (currentFrame) % numColumns;
	frameRow = (int)(currentFrame / numColumns);
	frameX = (0.0 + frameCol) / numColumns;
	frameX2 = (1.0 + frameCol) / numColumns;
	frameY = (0.0 + frameRow) / numberRows;
	frameY2 = (1.0 + frameRow) / numberRows;
}

void AnimationComponent::addAnimationState(AnimationState animState){
	m_animationStateList.push_back(animState);
}

void AnimationComponent::animate(){
	for (AnimationStateList::iterator it = m_animationStateList.begin(); it != m_animationStateList.end(); ++it){
		if (it->isActive()){
			Animation anim = it->getDirectionAnimation(currentDirection);
			currentFrame = anim.getFrameStart() + it->getOffset() % (anim.getFrameEnd() - anim.getFrameStart() + 1);

			updateVariables();

			if (it->getTimer() > it->getDelay()) {
				it->setOffset(it->getOffset() + 1);
				it->setTimer(0);
			}

			it->setTimer(it->getTimer() + 1);
		}
	}
}

AnimationState AnimationComponent::getAnimationState(std::string name){
	for (AnimationStateList::iterator it = m_animationStateList.begin(); it != m_animationStateList.end(); ++it){
		if (it->getName() == name){
			return *it;
		}
	}
}

void AnimationComponent::activateAnimationState(std::string name){
	for (AnimationStateList::iterator it = m_animationStateList.begin(); it != m_animationStateList.end(); ++it){
		if (it->getName() == name){
			it->setActive(true);
		}
		else{
			it->setActive(false);
		}
	}
}


