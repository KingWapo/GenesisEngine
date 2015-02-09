#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>

#include "GLSLProgram.h"
#include "SpriteBatch.h"
#include "Window.h"
#include "Camera2D.h"
#include "InputManager.h"
#include "Timing.h"

#include "Actor.h"

#include <vector>

enum class GameState { PLAY, EXIT };

typedef std::list<Actor> ActorList;

class MainGame
{
public:
	MainGame();
	~MainGame();

	void AddActor(Actor& newActor);

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void calculateFPS();
	void DrawActors();

	ActorList myActorList;

	Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	GLSLProgram _colorProgram;
	Camera2D _camera;
	SpriteBatch _spriteBatch;
	InputManager _inputManager;
	FpsLimiter _fpsLimiter;

	float _fps;
	float _maxFPS;
	float _time;
};

