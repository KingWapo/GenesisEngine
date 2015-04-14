#pragma once
#include "RenderableComponent.h"
#include "Transform2dComponent.h"
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

	int rightStandStart = 30;
	int rightStandEnd = 32;
	int rightMoveStart = 70;
	int rightMoveEnd = 79;
	int rightJumpStart = 74;
	int rightJumpEnd = 77;
	int rightFallStart = 73;
	int rightFallEnd = 74;

	int leftStandStart = 10;
	int leftStandEnd = 12;
	int leftMoveStart = 50;
	int leftMoveEnd = 59;
	int leftJumpStart = 55;
	int leftJumpEnd = 57;
	int leftFallStart = 54;
	int leftFallEnd = 55;

	float preLocationX;
	float preLocationY;

	bool direction = 1;

	int moveTimer = 0;
	int standTimer = 0;
	int jumpTimer = 0;
	int fallTimer = 0;

	int moveDelay = 4;
	int standDelay = 7;
	int jumpDelay = 3;
	int fallDelay = 20;

	int moveOffset = 0;
	int standOffset = 0;
	int jumpOffset = 0;
	int fallOffset = 0;

	boolean jumping = 0;
	boolean falling = 0;

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

	virtual bool vInit(void) override;
	virtual void vPostInit(void) override;
	virtual bool vUpdate(int deltaMs) override;
	virtual void vOnChanged(void) override;
	virtual void vDraw(void) override;

	void checkDirection();
	void animations();
	void updateVariables();
	void initVariables();
};

