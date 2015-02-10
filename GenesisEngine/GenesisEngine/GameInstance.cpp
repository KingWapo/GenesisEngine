#include "GameInstance.h"


GameInstance::GameInstance()
{
	m_ScreenWidth = 1024;
	m_ScreenHeight = 768;
	m_Time = 0;
	m_CurrentGameState = GameState::PLAY;
	m_MaxFps = 60.0f;
	m_Fps = 30.0f;

	m_Camera.Init(m_ScreenWidth, m_ScreenHeight);
}

GameInstance::GameInstance(int p_ScreenWidth, int p_ScreenHeight)
{
	m_ScreenWidth = p_ScreenWidth;
	m_ScreenHeight = p_ScreenHeight;
	m_Time = 0;
	m_CurrentGameState = GameState::PLAY;
	m_MaxFps = 60.0f;
	m_Fps = 30.0f;

	m_Camera.Init(m_ScreenWidth, m_ScreenHeight);
}



GameInstance::~GameInstance()
{
	// Prof. B: Cleanly delete all actors (maybe, just trying to get it to exit cleanly)
	while (!m_ActorList.empty())
	{
		(m_ActorList.back()).Destroy();
		m_ActorList.pop_back();
	}
}

void GameInstance::AddActor(Actor &p_NewActor)
{
	m_ActorList.push_back(p_NewActor);
}

void GameInstance::Run()
{
	Init();

	Update();
}

void GameInstance::Init()
{
	m_Window.Create("The Genesis Engine", m_ScreenWidth, m_ScreenHeight, 0);

	InitShaders();
}


// Need to create dynamic shader use
void GameInstance::InitShaders()
{
	m_ColorProgram.CompileShaders("Shaders\\colorShading.vert", "Shaders\\colorShading.frag");
	m_ColorProgram.LinkShaders();
}

void GameInstance::Update()
{
	while (m_CurrentGameState != GameState::EXIT)
	{
		// Process Input
		// InputManager.Update() or such

		// Update Everything
		m_Camera.Update();
		
		for (ActorList::iterator actor = m_ActorList.begin(); actor != m_ActorList.end(); ++actor)
		{
			(*actor).Update(1.0 / m_Fps);
		}

		// Render Everything
		Draw();
	}
}

void GameInstance::Draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ColorProgram.Use();
	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation = m_ColorProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = m_Camera.GetCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	DrawActors();

	glBindTexture(GL_TEXTURE_2D, 0);
	m_ColorProgram.Unuse();

	m_Window.SwapBuffer();
}

void GameInstance::DrawActors()
{
	for (ActorList::iterator it = m_ActorList.begin(); it != m_ActorList.end(); ++it)
	{
		(*it).Draw();
	}
}