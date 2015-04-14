#pragma once
#include "RenderableComponent.h"
#include "Transform2dComponent.h"
#include "ActorComponent.h"
#include "Actor.h"
#include "Window.h"
#include "Animation.h"
#include "AnimationState.h"

#include "SDL\SDL.h"

typedef std::list<AnimationState> AnimationStateList;

class AnimationComponent : public RenderableComponent
{
private:
	AnimationStateList m_animationStateList;

	int totFrames;
	int numColumns;
	int numberRows;
	int currentFrame; // Matt: [0,totalFrames-1]
	int frameCol;
	int frameRow; 
	double frameX;
	double frameX2;
	double frameY;
	double frameY2;

	int currentDirection = 0;

	SDL_Texture* m_sprite;
	SDL_Surface* m_screen;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	SDL_Rect m_source;
	SDL_Rect m_position;

	GLuint TextureID;

	shared_ptr<Transform2dComponent> m_transform;
public:
	AnimationComponent();
	AnimationComponent(const char* p_fileLocation, int totalFrames, int numberColumns, Point2DF p_location, Point2DF p_size, Point2DF p_cell, Window* p_window);
	~AnimationComponent();

	static const char* g_Name;

	virtual bool vInit(void) override;
	virtual void vPostInit(void) override;
	virtual bool vUpdate(int deltaMs) override;
	virtual void vOnChanged(void) override;
	virtual void vDraw(void) override;
	virtual const char* VGetName() const { return g_Name; }

	void animate();
	void addAnimationState(AnimationState animState);
	AnimationState getAnimationState(std::string name);
	void activateAnimationState(std::string name);
	void updateVariables();

	void setCurrentDirection(int dir){ currentDirection = dir; }
	int getCurrentDirection(){ return currentDirection; }
};

