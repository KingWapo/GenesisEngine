#pragma once

#include "EngineCode.h"
#include "Actor.h"
#include "Transformation.h"

class TestGameApp : public EngineApp
{
protected:
	virtual BaseGameLogic *VCreateGameAndView();

public:
	virtual TCHAR *VGetGameTitle() { return _T("Test Game"); }
	virtual TCHAR *VGetGameAppDirectory() { return _T("Genesis Engine\\Test App"); }
	virtual HICON VGetIcon();

protected:
	virtual void VRegisterGameEvents(void);
	virtual void VCreateNetworkEventForwarder(void);
	virtual void VDestroyNetworkEventForwarder(void);
};

class TestGameLogic : public BaseGameLogic
{
public:
	TestGameLogic();
	virtual ~TestGameLogic();

	/* Update */
	virtual void VSetProxy();
	//virtual void VMoveActor(const ActorId id, Transformation2d const trans);

	/* Overloads */
	// ChangeState
	virtual void VAddView(shared_ptr<IGameView> pView, ActorId actorId = INVALID_ACTOR_ID);
	// Get Physics
	virtual std::shared_ptr<IGamePhysics> VGetGamePhysics();

	/* Event Delegates */

protected:
	virtual bool VLoadGameDelegate();
};