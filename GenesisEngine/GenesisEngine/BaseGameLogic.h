#pragma once

//#include "Includes.h"
#include "interfaces.h"
#include "ProcessManager.h"
#include "Math.h"

class LevelManager;

enum BaseGameState
{
	BGS_Invalid,
	BGS_Initializing,
	BGS_MainMenu,
	BGS_WaitingForPlayers,
	BGS_LoadingGameEnvironment,
	BGS_WaitingForPlayersToLoadEnvironment,
	BGS_SpawningPlayersActors,
	BGS_Running
};

typedef std::map<ActorId, StrongActorPtr> ActorMap;
typedef std::string Level;

class LevelManager
{
protected:
	std::vector<Level> m_Levels;
	int m_CurrentLevel;

public:
	const std::vector<Level> &GetLevels() const { return m_Levels; }
	const int GetCurrentLevel() const { return m_CurrentLevel; }
	bool Initialize(std::vector<std::string> &levels);
};

class BaseGameLogic : public IGameLogic
{
	friend class EngineApp;			// This is only to gain access to the view list

protected:
	float m_Lifetime;					// Indicates how long this game has been in session
	ProcessManager *m_pProcessManager;	// A game logic entity
	GCCRandom m_random;					// Our Random Number Generator
	ActorMap m_actors;
	ActorId m_LastActorId;
	BaseGameState m_State;				// game state: loading, running, etc.
	int m_ExpectedPlayers;				// how many local human players
	int m_ExpectedRemotePlayers;		// expected remote players
	int m_ExpectedAI;					// how many AI players
	int m_HumanPlayersAttached;
	int m_AIPlayersAttached;
	int m_HumanGamesLoaded;
	GameViewList m_gameViews;			// views that are attached to our game
	//Pathing graph
	//ActorFactory

	bool m_bProxy;						// set if this is a proxy game logic, not a real one
	int m_remotePlayerId;				// If we are a remote player - what is our socket number on the server

	// Render Diagnostics
	// Physics

	LevelManager *m_pLevelManager;		// Manages loading and chaining levels
	

public:
	BaseGameLogic();
	virtual ~BaseGameLogic();
	bool Init(void);

	void SetProxy(bool isProxy)
	{
		m_bProxy = isProxy;
	}
	const bool IsProxy() const { return m_bProxy; }

	// Or other Script
	const bool CanRunLua() const { return !IsProxy() || GetState() != BGS_Running; }

	ActorId GetNewActorID(void)
	{
		return ++m_LastActorId;
	}

	// Pathing Graph
	GCCRandom &GetRNG(void) { return m_random; }

	virtual void VAddView(shared_ptr<IGameView> pView, ActorId actorId = INVALID_ACTOR_ID);
	virtual void VRemoveView(shared_ptr<IGameView> pView);

	virtual StrongActorPtr VCreateActor(const std::string &actorResource /*, TiXmlElement *overrides, const Mat4x4 *initialTransform=NULL */, const ActorId serversActorId = INVALID_ACTOR_ID);
	virtual void VDestroyActor(const ActorId actorId);
	virtual WeakActorPtr VGetActor(const ActorId actorId);
	virtual void VModifyActor(const ActorId actorId /*, TiXmlElement *overrides */);
	
	virtual void VMoveActor(const ActorId id /*, Mat4x4 const &mat*/) {}

	// editor functions
	std::string GetActorXml(const ActorId id);

	// Level management
	const LevelManager *GetLevelManager() { return m_pLevelManager; }
	virtual bool VLoadGame(const char *levelResource) override;
	virtual void VSetProxy();

	// Logic Update
	virtual void VOnUpdate(float tiem, float elapsedTime);

	// Changing Game Logic State
	virtual void VChangeState(BaseGameState newState);
	const BaseGameState GetState() const { return m_State; }

	// Render Diagnostics

	void AttachProcess(StrongProcessPtr pProcess) { if (m_pProcessManager) { m_pProcessManager->AttachProcess(pProcess); } }

	// Event Delegates
	// void RequestDestroyActorDelegate(IEventDataPtr pEventData);

protected:
	// ActorFactory

	virtual bool VLoadGameDelegate() { return true; }

	//void MoveActorDelegate(IEventDataPtr pEventData);
	//void RequestNewActorDelegate(IEventDataPtr pEventData);
};

