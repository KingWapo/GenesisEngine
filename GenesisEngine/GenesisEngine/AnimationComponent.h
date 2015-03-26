#pragma once
#include "RenderableComponent.h"
#include "Transform2dComponent.h"
#include "Actor.h"
#include "Window.h"

#include "SDL\SDL.h"

class AnimationComponent : public RenderableComponent
{
private:
	int totalFrames = 80;
	int numberColumns = 10;
	int numberRows = totalFrames / numberColumns;
	int currentFrame = 0; // Matt: [0,totalFrames-1]
	int frameCol = (currentFrame) % numberColumns;
	int frameRow = (int) (currentFrame / numberColumns); 
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

	bool left = 0;
	bool right = 1;

	int moveTimer = 0;
	int standTimer = 0;
	int moveDelay = 7;
	int standDelay = 7;
	int offset = 0;

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
	AnimationComponent(const char* p_fileLocation, Point2DF p_location, Point2DF p_size, Point2DF p_cell, Window* p_window);
	~AnimationComponent();

	virtual bool vInit(void) override;
	virtual void vPostInit(void) override;
	virtual bool vUpdate(int deltaMs) override;
	virtual void vOnChanged(void) override;
	virtual void vDraw(void) override;

	void checkDirection();
	void animations();
	void updateVariables();
};

