#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>

#include "GLSLProgram.h"
#include "Window.h"
#include "Camera2D.h"
#include "InputManager.h"

#include "Actor.h"

#include <vector>

enum class GameState { PLAY, EXIT };

typedef std::list<Actor> ActorList;

class GameInstance
{
public:
	GameInstance();
	GameInstance(int p_ScreenWidth, int p_ScreenHeight);
	~GameInstance();

	void AddActor(Actor &newActor);

	void Run();

private:
	void Init();
	void InitShaders();
	void Update();
	void Draw();
	void DrawActors();
	void CalculateFPS();

	ActorList m_ActorList;

	GLSLProgram m_ColorProgram;
	InputManager m_InputManager;
	Window m_Window;
	int m_ScreenWidth;
	int m_ScreenHeight;
	GameState m_CurrentGameState;

	Camera2D m_Camera;
	
	float m_Fps;
	float m_MaxFps;
	float m_Time;
};

