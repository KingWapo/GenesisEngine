// GenesisEngine.cpp : Defines the entry point for the Engine

#include "EngineCode.h"
#include "TestGame.h"
#include "InputManager.h"
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
	GameInstance *instance = new GameInstance();	// Prof. B: Switched to dynamic allocation so could control when destructor is called
	instance->Init();
	Actor freddy(0);
	Scene* myScene = new Scene();
	SDLRenderableComponent renderComp("Textures\\jimmyJump_pack\\PNG\\CharacterRight_Standing.png",Vector2(100.0,100.0), Vector2(73.0, 79.0), Vector2(0.0, 0.0), instance->getWindow());
		//Vector2(0.0, 0.0), Vector2(100.0, 100.0), "Textures\\jimmyJump_pack\\PNG\\CharacterRight_Standing.png");
	StrongActorComponentPtr pRenderComp = StrongActorComponentPtr(&renderComp);
	myScene->addRenderableComponent(pRenderComp);
	instance->setScene(myScene);
	freddy.AddComponent(pRenderComp, true);

	InputManager inputComp;
	StrongActorComponentPtr pInputComp = StrongActorComponentPtr(&inputComp);
	freddy.AddComponent(pInputComp, false);

	instance->AddActor(freddy);
	
	// Runs the instance of a game.
	// When it passes this line, the game is over.
	instance->Run();

	// Cleanup
	freddy.Destroy();
	delete myScene;
	delete instance;	// Prof. B: Force call of destructor BEFORE logger is destroyed

	// Shutdown
	Logger::Destroy();

	int exitCode = g_pApp->GetExitCode();
	return exitCode;
}
