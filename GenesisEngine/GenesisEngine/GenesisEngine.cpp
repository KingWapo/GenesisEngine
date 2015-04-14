// GenesisEngine.cpp : Defines the entry point for the Engine

#include "EngineCode.h"
#include "TestGame.h"
#include "KeyboardInput.h"
#include "CustomScript.h"
#include "Transform2dComponent.h"
#include "RectCollidableComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include <iostream>
#include "Actor.h"
#include "ActorFactory.h"
#include "GameInstance.h"
#include "SDLRenderableComponent.h"
#include "Scene.h"
#include "EngineController.h"

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

	//			Adam - Testing Controller
	// Creates instance and scene within the controller
	EngineController *p_controller = new EngineController();

	//Matt- adding background
	p_controller->addActor();
	p_controller->setActorTranslation(Vector2(0, 0));
	p_controller->addSDLRenderable("Textures/skyGrassBackground.png", Point2DF(1.3333, 1), Point2DF(0, 0));

	// Creates new Actor, and sets it as selectedActor
	p_controller->addActor();

	// Set actor location
	p_controller->setActorTranslation(Vector2(.2f, .4f)); //

	// Add on required components

		// Animation
	p_controller->addAnimation("Textures/linkSpriteSheet.png", 80, 10, Point2DF(0.073f, 0.079f), Point2DF(0, 0));
		//
		// Physics
	p_controller->addPhysics(); //

		// Rect Collider
	p_controller->addRectCollidable(0.073f, 0.079f, false);
	//p_controller->addCircCollidable(0.079f / 2, false);

		// Input Manager
	//p_controller->addKeyboardInput(); //

		// Controller Input
	p_controller->addControllerInput();

		// Side Scroller
	p_controller->addSideScrollerController(); //

		// Top Down
	//p_controller->addTopDownController();

	float x = .4f;
	float y = .4f;
	float w = .052f;
	float h = .052f;

	// Add second actor and set it to selectedActor
	p_controller->addActor();
	p_controller->setActorTranslation(Vector2(x, y));

	// Add components to selectedActor

		// SDL Render
	p_controller->addSDLRenderable("Textures/jimmyJump_pack/PNG/LandPiece_LightGreen.png", Point2DF(w, h), Point2DF(0, 0));

		// Rect Collidable
	p_controller->addRectCollidable(w, h, true);
	//p_controller->addCircCollidable(h / 2, true);

	// Run the controller
	p_controller->run();

	// Clean up
	delete p_controller;

	// Shutdown
//	Logger::Destroy();

	int exitCode = g_pApp->GetExitCode();
	return exitCode;
}
