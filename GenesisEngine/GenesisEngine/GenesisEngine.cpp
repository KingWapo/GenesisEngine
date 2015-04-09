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
	p_controller->addAnimation("Textures/linkSpriteSheet.png", Point2DF(0.073f, 0.079f), Point2DF(0, 0));
		//
		// Physics
	p_controller->addPhysics(); //

		// Rect Collider
	p_controller->addRectCollidable(0.073f, 0.079f, false);
	//p_controller->addCircCollidable(0.079f / 2, false);

		// Input Manager
	p_controller->addKeyboardInput(); //

		// Side Scroller
	//p_controller->addSideScrollerController(); //

		// Top Down
	p_controller->addTopDownController();

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


	/*
	GameInstance *p_instance = new GameInstance();
	p_instance->Init();
	StrongActorPtr freddy(new Actor(0));
	Scene* myScene = new Scene();

	Transform2dComponent *p_transformComp = new Transform2dComponent();
	p_transformComp->SetTranslation(Vector2(.2f, .4f));
	StrongActorComponentPtr pTransformComp = StrongActorComponentPtr(p_transformComp);
	freddy->AddComponent(pTransformComp, false);*/

	//John - using animation component instead for player character
	/*SDLRenderableComponent *p_renderComp = new SDLRenderableComponent("Textures/linkSpriteSheet.png",
		Point2DF(.100f, .100f), Point2DF(.073f, .079f), Point2DF(0, 0), p_instance->getWindow());
	StrongActorComponentPtr pRenderComp = StrongActorComponentPtr(p_renderComp);
	myScene->addRenderableComponent(pRenderComp);
	p_instance->setScene(myScene);
	freddy->AddComponent(pRenderComp, true);*/

	/*
	AnimationComponent *p_animComp = new AnimationComponent("Textures/linkSpriteSheet.png",
		Point2DF(.100f, .100f), Point2DF(.073f, .079f), Point2DF(0, 0), p_instance->getWindow());
	StrongActorComponentPtr pAnimComp = StrongActorComponentPtr(p_animComp);
	myScene->addRenderableComponent(pAnimComp);
	p_instance->setScene(myScene);
	freddy->AddComponent(pAnimComp, true);*/

	/*
	PhysicsComponent physicsComp;
	StrongActorComponentPtr pPhysicsComp = StrongActorComponentPtr(&physicsComp);
	freddy->AddComponent(pPhysicsComp, false);

	RectCollidableComponent rectColComp(.073f, .079f, false);
	StrongActorComponentPtr pRectColComp = StrongActorComponentPtr(&rectColComp);
	freddy->AddComponent(pRectColComp, false);

	KeyboardInput *p_inputComp = new KeyboardInput();
	StrongActorComponentPtr pInputComp = StrongActorComponentPtr(p_inputComp);
	freddy->AddComponent(pInputComp, false);

	CustomScript *p_customScript = new CustomScript();
	StrongActorComponentPtr pCustomScript = StrongActorComponentPtr(p_customScript);
	freddy->AddComponent(pCustomScript, false);

	p_instance->AddActor(freddy.get());*/

	/*
	StrongActorPtr rock(new Actor(1));

	Transform2dComponent *p_rockTransform = new Transform2dComponent();
	p_rockTransform->SetTranslation(Vector2(x, y));
	StrongActorComponentPtr pRockTransform = StrongActorComponentPtr(p_rockTransform);
	rock->AddComponent(pRockTransform, false);

	SDLRenderableComponent *p_rockRender = new SDLRenderableComponent("Textures/jimmyJump_pack/PNG/LandPiece_LightGreen.png",
		Point2DF(x, y), Point2DF(w, h), Point2DF(0, 0), p_instance->getWindow());
	StrongActorComponentPtr pRockRender = StrongActorComponentPtr(p_rockRender);
	myScene->addRenderableComponent(pRockRender);
	rock->AddComponent(pRockRender, false);

	RectCollidableComponent rockRectCol(w, h, true);
	StrongActorComponentPtr pRockRectCol = StrongActorComponentPtr(&rockRectCol);
	rock->AddComponent(pRockRectCol, false);

	p_instance->AddActor(rock.get());*/
	
	// Runs the instance of a game.
	// When it passes this line, the game is over.
	//p_instance->Run();

	// Cleanup
	//delete myScene;
	//delete p_instance;

	// Shutdown
//	Logger::Destroy();

	int exitCode = g_pApp->GetExitCode();
	return exitCode;
}
