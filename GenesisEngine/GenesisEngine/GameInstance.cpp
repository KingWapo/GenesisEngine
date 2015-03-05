#include "GameInstance.h"
#include "Render.h"
#include "Scene.h"
#include "RectCollidableComponent.h"

GameInstance::GameInstance()
{
	m_ScreenWidth = 1024;
	m_ScreenHeight = 768;
	m_Time = 0;
	m_CurrentGameState = GameState::PLAY;
	m_MaxFps = 60.0f;
	m_Fps = 30.0f;
	m_scene = NULL;
	m_ActorList = {};

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
	m_scene = NULL;
	m_ActorList = {};

	m_Camera.Init(m_ScreenWidth, m_ScreenHeight);
}



GameInstance::~GameInstance()
{
	while (!m_ActorList.empty())
	{
		Actor *p_temp = m_ActorList.back();
		m_ActorList.pop_back();
		if (p_temp != NULL)
		{
			p_temp->Destroy();
		}
		delete p_temp;
		
	}
	/*for (ActorList::iterator it = m_ActorList.begin(); it != m_ActorList.end(); ++it)
	{
		(*it)->Destroy();

	}*/
	//John - removed deleting to get rid of assertion error
	delete m_Window;
}

void GameInstance::AddActor(Actor* p_NewActor)
{
	m_ActorList.push_back(p_NewActor);
}

void GameInstance::Run()
{
	if (!isInitialized)
	{
		Init();
	}

	Update();
}

void GameInstance::Init()
{
	isInitialized = true;
	m_Window = new Window();
	m_Window->Create("The Genesis Engine", m_ScreenWidth, m_ScreenHeight, 0);

	InitShaders();
}


// Need to create dynamic shader use
void GameInstance::InitShaders()
{
	m_ColorProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_ColorProgram.LinkShaders();
}

void GameInstance::Update()
{
	// Start with an initial refresh
	bool refreshRender = true;
	bool refreshInput = true;
	bool processMotion = true;

	SDL_Event e;
	while (m_CurrentGameState != GameState::EXIT)
	{
		SDL_PollEvent(&e);
		switch (e.type)
		{
			// Queue to quit
			case SDL_QUIT: m_CurrentGameState = GameState::EXIT; break;

			// Queue a render refresh
			case SDL_WINDOWEVENT: case SDL_SYSWMEVENT:
				refreshRender = true;
			break;

			// Queue a keyboard or input event
			case SDL_KEYDOWN: case SDL_KEYUP:
			case SDL_JOYBUTTONDOWN: case SDL_JOYBUTTONUP:
			case SDL_CONTROLLERBUTTONDOWN: case SDL_CONTROLLERBUTTONUP:
			case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
			case SDL_FINGERDOWN: case SDL_FINGERUP:
				refreshInput = true;
			break;

			// Queue a motion event
			case SDL_MOUSEMOTION:
			case SDL_CONTROLLERAXISMOTION:
			case SDL_FINGERMOTION:
				processMotion = true;
			break;
		}

		// Process Input
		if (refreshInput || processMotion)
		{
			// InputManager.Update() or such
			refreshInput = processMotion = false;
		}

		// Update components
		refreshRender = refreshRender | UpdateActors();

		// Render Everything (forcing a redraw for now, SDL events are not firing right)
		if (m_scene != NULL) // && refreshRender)
		{
			Draw();
			refreshRender = false;
		}
	}
}

bool GameInstance::UpdateActors()
{
	bool stateChanged = false;

	// These update function should return a boolean that indicates if something actually
	// changed or not.  If not, you don't need to re-render the screen.
	stateChanged = stateChanged | m_Camera.Update();

	for (ActorList::iterator actor = m_ActorList.begin(); actor != m_ActorList.end(); ++actor)
	{
		stateChanged = stateChanged | (*actor)->Update((1.0 / m_Fps) * 1000);

		shared_ptr<RectCollidableComponent> collider = (*actor)->GetComponent<RectCollidableComponent>("RectCollidableComponent");
		if (collider.get() != NULL) {
			for (ActorList::iterator actorOther = m_ActorList.begin(); actorOther != m_ActorList.end(); ++actorOther) {
				shared_ptr<RectCollidableComponent> colliderOther = (*actorOther)->GetComponent<RectCollidableComponent>("RectCollidableComponent");

				if (colliderOther.get() != NULL) {
					if (collider->isColliding(*colliderOther.get())) {
						printf("object collision\n %s \n", collider->getTransform().GetTranslation().toString().c_str()); fflush(stdout);
						//collider->resolveCollision(colliderOther);
					}
				}
			}
		}
	}

	return stateChanged;
}

void GameInstance::Draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//m_ColorProgram.Use();
	glActiveTexture(GL_TEXTURE0);

	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	if (m_Window != NULL) {
		float ratio = m_Window->GetScreenWidth() / (float)m_Window->GetScreenHeight();
		glOrtho(0.0, ratio, 0.0, 1.0, 0.0, 1.0);
	}

	glMatrixMode(GL_MODELVIEW); glLoadIdentity();

	//GLuint pLocation = m_ColorProgram.GetUniformLocation("P");
	//glm::mat4 cameraMatrix = m_Camera.GetCameraMatrix();

	//glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	DrawActors();

	glBindTexture(GL_TEXTURE_2D, 0);
	//m_ColorProgram.Unuse();

	m_Window->SwapBuffer();
}

void GameInstance::DrawActors()
{
	for (ActorList::iterator it = m_ActorList.begin(); it != m_ActorList.end(); ++it)
	{
		(*it)->Draw();
	}
}