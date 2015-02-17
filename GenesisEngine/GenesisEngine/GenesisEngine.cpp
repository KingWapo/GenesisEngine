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


#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

using namespace std;

/*
#if defined(_M_IX86)
	#if defined(_DEBUG)
		#pragma comment(lib, "bulletcollision_debug.lib")
		#pragma comment(lib, "bulletdynamics_debug.lib")
		#pragma comment(lib, "linearmath_debug.lib")
	#else
		#pragma comment(lib, "bulletcollision.lib")
		#pragma comment(lib, "bulletdynamics.lib")
		#pragma comment(lib, "linearmath.lib")
	#endif
#elif defined(_M_X64)
	#if defined(_DEBUG)
		#pragma comment(lib, "bulletcollision_x64__debug.lib")
		#pragma comment(lib, "bulletdynamics_x64__debug.lib")
		#pragma comment(lib, "linearmath_x64_debug.lib")
	#else
		#pragma comment(lib, "bulletcollision_x64.lib")
		#pragma comment(lib, "bulletdynamics_x64.lib")
		#pragma comment(lib, "linearmath_x64.lib")
	#endif
#else
#error Preprocessor defines can't figure out which Bullet library to use.
#endif
*/ // Not sure if needed now, until our own physics is up.

#pragma comment(lib, "zlibstat.lib")

#pragma comment(lib, "libogg_static.lib")
#pragma comment(lib, "libvorbis_static.lib")
#pragma comment(lib, "libvorbisfile_static.lib")

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
