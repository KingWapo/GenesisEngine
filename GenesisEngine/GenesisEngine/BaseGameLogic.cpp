//#include <mmsystem.h>

#include "BaseGameLogic.h"

// LevelManager implementation
bool LevelManager::Initialize(std::vector<std::string> &levels)
{
	std::vector<std::string>::iterator i = levels.begin();
	while (i != levels.end())
	{
		m_Levels.push_back(*i);
		++i;
	}
	return true;
}

// BaseGameLogic implementation
BaseGameLogic::BaseGameLogic()
{
	m_LastActorId = 0;
	m_Lifetime = 0;
	m_pProcessManager = GCC_NEW ProcessManager;
	m_random.Randomize();
	m_State = BGS_Initializing;
	m_bProxy = false;
	// Render Diagnostics
	m_ExpectedPlayers = 0;
	m_ExpectedRemotePlayers = 0;
	m_ExpectedAI = 0;
	m_HumanPlayersAttached = 0;
	m_AIPlayersAttached = 0;
	m_HumanGamesLoaded = 0;
	//Pathing Graph
	//Actor Factory

	m_pLevelManager = GCC_NEW LevelManager;
	GCC_ASSERT(m_pProcessManager &&m_pLevelManager);
	//m_pLevelManager->Initialize(g_pApp->m_ResCache->Match("world\\*.xml"));

	//RegisterEngineScriptEvents();
}

BaseGameLogic::~BaseGameLogic()
{
	while (!m_gameViews.empty())
		m_gameViews.pop_front();

	SAFE_DELETE(m_pLevelManager);
	SAFE_DELETE(m_pProcessManager);
	//SAFE_DELETE(m_pActorFactory);

	// Destroy all actors
	/*
	for (auto it = m_actors.begin(); it != m_actors.end(); ++it)
	{
		it->second->Destroy();
	}
	m_actors.clear();
	*/

	// EventManager
}

bool BaseGameLogic::Init(void)
{
	// Actor Factory
	// Pathing Graph

	// Event Manager
	return true;
}

std::string BaseGameLogic::GetActorXml(const ActorId id)
{
	//Stuff with xml

	return "No Actor";
}

bool BaseGameLogic::VLoadGame(const char *levelResource)
{
	// XML Stuff

	// More xml stuff

	return true;
}

void BaseGameLogic::VSetProxy()
{
	m_bProxy = true;

	// Event Manager

	// Physics
}

StrongActorPtr BaseGameLogic::VCreateActor(const std::string &actorResource, const ActorId serversActorId)
{
	/* Stuff and things for when actors are in*/

	return StrongActorPtr();
}

void BaseGameLogic::VDestroyActor(const ActorId actorId)
{
	// Actors
}

WeakActorPtr BaseGameLogic::VGetActor(const ActorId actorId)
{
	ActorMap::iterator findIt = m_actors.find(actorId);
	if (findIt != m_actors.end())
		return findIt->second;
	return WeakActorPtr();
}

void BaseGameLogic::VModifyActor(const ActorId actorId)
{
	// Actor Factory

	auto findIt = m_actors.find(actorId);
	if (findIt != m_actors.end())
	{
		// Actor Factory
	}
}

void BaseGameLogic::VOnUpdate(float time, float elapsedTime)
{
	int deltaMilliseconds = int(elapsedTime * 1000.0f);
	m_Lifetime += elapsedTime;

	switch (m_State)
	{
		case BGS_Initializing:
			// If we get to here we're ready to attach players
			VChangeState(BGS_MainMenu);
			break;

		case BGS_MainMenu:
			break;

		case BGS_LoadingGameEnvironment:
			break;

		case BGS_WaitingForPlayersToLoadEnvironment:
			if (m_ExpectedPlayers + m_ExpectedRemotePlayers <= m_HumanGamesLoaded)
			{
				VChangeState(BGS_SpawningPlayersActors);
			}
			break;

		case BGS_SpawningPlayersActors:
			VChangeState(BGS_Running);
			break;

		case BGS_WaitingForPlayers:
			/*
			if (m_ExpectedPlayers + m_ExpectedRemotePlayers == m_HumanPlayersAttached)
			{
				// The server sends us the level name as a part of the login message. 
				// We have to wait until it arrives before loading the level
				if (!g_pApp->m_Options.m_Level.empty())
				{
					VChangeState(BGS_LoadingGameEnvironment);
				}
			}*/
			break;

		case BGS_Running:
			m_pProcessManager->UpdateProcesses(deltaMilliseconds);
			/*
			if (m_pPhysics && !m_bProxy)
			{
				m_pPhysics->VOnUpdate(elapsedTime);
				m_pPhysics->VSyncVisibleScene();
			}
			*/
			break;

		default:
			GCC_ERROR("Unrecognized state.");
	}

	// update all game views
	for (GameViewList::iterator it = m_gameViews.begin(); it != m_gameViews.end(); ++it)
	{
		(*it)->VOnUpdate(deltaMilliseconds);
	}

	// Update game actors
}

void BaseGameLogic::VChangeState(BaseGameState newState)
{
	if (newState == BGS_WaitingForPlayers)
	{
		// Get rid of the Main menu....
		m_gameViews.pop_front();

		// set up expected players

		// Game options
	}
	else if (newState == BGS_LoadingGameEnvironment)
	{
		m_State = newState;
		/*
		if (!g_pApp->VLoadGame())
		{
			GCC_ERROR("The game failed to load.");
			g_pApp->AbortGame();
		}
		else
		{
			VChangeState(BGS_WaitingForPlayersToLoadEnvironment);			// we must wait for all human player to report their environments are loaded.
			return;
		}
		*/
	}

	m_State = newState;
}

// RenderDiagnostics

void BaseGameLogic::VAddView(shared_ptr<IGameView> pView, ActorId actorId)
{
	// This makes sure that all views havea non-zero view id;
	int viewId = static_cast<int>(m_gameViews.size());
	m_gameViews.push_back(pView);
	pView->VOnAttach(viewId, actorId);
	pView->VOnRestore();
}

void BaseGameLogic::VRemoveView(shared_ptr<IGameView> pView)
{
	m_gameViews.remove(pView);
}

// Create Actor Factory

// RequestDestroyActorDelegate

// MoveActorDelegate

// RequestNewActorDelegate