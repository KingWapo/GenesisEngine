// GenesisEngine.cpp : Defines the entry point for the Engine

#include "EngineCode.h"
#include "TestGame.h"
#include "InputManager.h"
#include <iostream>
#include "MainGame.h"
#include "Actor.h"
#include "ActorFactory.h"


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

// MiniDump

// Entry point to the program. Initializes everything and goes into a message processing
// loop. Idle time is used to render the scene.
/*
INT WINAPI GenesisEngine(HINSTANCE hInstance,
						 HINSTANCE hPrevInstance,
						 LPWSTR	   lpCmdLine,
						 int	   nCmdShow)
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

	//g_pApp->m_Options.Init();

	if (!g_pApp->InitInstance(hInstance, lpCmdLine, 0, g_pApp->m_Options.m_ScreenSize.x, g_pApp->m_Options.m_ScreenSize.y))
	{
		return FALSE;
	}

	// Main Loop

	// Shutdown

	Logger::Destroy();

	return g_pApp->GetExitCode();
}
*/


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
	MainGame* mainGame = new MainGame();	// Prof. B: Switched to dynamic allocation so could control when destructor is called
	Actor freddy(0);
	Renderer2dComponent renderComp(Vector2(0.0, 0.0), Vector2(100.0, 100.0), "Textures\\jimmyJump_pack\\PNG\\CharacterRight_Standing.png");
	StrongActorComponentPtr pRenderComp = StrongActorComponentPtr(&renderComp);
	freddy.AddComponent(pRenderComp);

	mainGame->AddActor(freddy);
	mainGame->run();

	// Cleanup
	freddy.Destroy();
	delete mainGame;	// Prof. B: Force call of destructor BEFORE logger is destroyed

	// Shutdown
	Logger::Destroy();

	int exitCode = g_pApp->GetExitCode();
	return exitCode;
}
