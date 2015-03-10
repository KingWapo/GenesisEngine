// GenesisEngine.cpp : Defines the entry point for the Engine

#include "EngineCode.h"
#include "TestGame.h"
#include "InputManager.h"
#include "CustomScript.h"
#include "Transform2dComponent.h"
#include "RectCollidableComponent.h"
#include "PhysicsComponent.h"
#include <iostream>
#include "Actor.h"
#include "ActorFactory.h"
#include "GameInstance.h"
#include "SDLRenderableComponent.h"
#include "Scene.h"

using namespace std;

int GenesisEntry(int argc, char *argv[])
{
	
	// Set up checks for memory leaks
	int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	// _CRTDBG_LEAK_CHECK_DF is used at program initialization to force
	// a leak check just before program exit. This is important because
	// some classes may dynamically allocate memory in globally constructed
	// objects.
	
	tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;

	_CrtSetDbgFlag(tmpDbgFlag);

	// Initialize the logging system
	Logger::Init("logging.xml");

	g_pApp = GCC_NEW TestGameApp();
	g_pApp->m_pGame = GCC_NEW TestGameLogic();

	//g_pApp->m_Options.Init();

	if (!g_pApp->InitInstance())
	{
		return FALSE;
	}

	// Main Loop
	GameInstance *p_instance = new GameInstance();
	p_instance->Init();
	StrongActorPtr freddy(new Actor(0));
	Scene* myScene = new Scene();

	Transform2dComponent *p_transformComp = new Transform2dComponent();
	StrongActorComponentPtr pTransformComp = StrongActorComponentPtr(p_transformComp);
	freddy->AddComponent(pTransformComp, false);

	SDLRenderableComponent *p_renderComp = new SDLRenderableComponent("Textures/robotSpriteSheet.png",
		Point2DF(.100f, .100f), Point2DF(.073f, .079f), Point2DF(0, 0), p_instance->getWindow());
	StrongActorComponentPtr pRenderComp = StrongActorComponentPtr(p_renderComp);
	myScene->addRenderableComponent(pRenderComp);
	p_instance->setScene(myScene);
	freddy->AddComponent(pRenderComp, true);

	PhysicsComponent physicsComp;
	StrongActorComponentPtr pPhysicsComp = StrongActorComponentPtr(&physicsComp);
	freddy->AddComponent(pPhysicsComp, false);

	RectCollidableComponent rectColComp(.073f, .079f, false);
	StrongActorComponentPtr pRectColComp = StrongActorComponentPtr(&rectColComp);
	freddy->AddComponent(pRectColComp, false);

	InputManager *p_inputComp = new InputManager();
	StrongActorComponentPtr pInputComp = StrongActorComponentPtr(p_inputComp);
	freddy->AddComponent(pInputComp, false);

	CustomScript *p_customScript = new CustomScript();
	StrongActorComponentPtr pCustomScript = StrongActorComponentPtr(p_customScript);
	freddy->AddComponent(pCustomScript, false);

	p_instance->AddActor(freddy.get());

	StrongActorPtr rock(new Actor(1));

	Transform2dComponent *p_rockTransform = new Transform2dComponent();
	p_rockTransform->SetTranslation(Vector2(.4f, .4f));
	StrongActorComponentPtr pRockTransform = StrongActorComponentPtr(p_rockTransform);
	rock->AddComponent(pRockTransform, false);

	SDLRenderableComponent *p_rockRender = new SDLRenderableComponent("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png",
		Point2DF(.400f, .400f), Point2DF(.073f, .079f), Point2DF(0, 0), p_instance->getWindow());
	StrongActorComponentPtr pRockRender = StrongActorComponentPtr(p_rockRender);
	myScene->addRenderableComponent(pRockRender);
	rock->AddComponent(pRockRender, false);

	RectCollidableComponent rockRectCol(.073f, .079f, true);
	StrongActorComponentPtr pRockRectCol = StrongActorComponentPtr(&rockRectCol);
	rock->AddComponent(pRockRectCol, false);

	p_instance->AddActor(rock.get());
	
	// Runs the instance of a game.
	// When it passes this line, the game is over.
	p_instance->Run();

	// Cleanup
	delete myScene;
	delete p_instance;

	// Shutdown
//	Logger::Destroy();

	int exitCode = g_pApp->GetExitCode();
	return exitCode;
}
