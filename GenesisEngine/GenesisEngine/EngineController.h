#pragma once
#include "EngineCode.h"
#include "TestGame.h"
#include "KeyboardInput.h"
#include "Controller360Input.h"
#include "CustomScript.h"
#include "Transform2dComponent.h"
#include "RectCollidableComponent.h"
#include "CircCollidableComponent.h"
#include "SideScrollerController.h"
#include "TopDownController.h"
#include "PhysicsComponent.h"
#include <iostream>
#include "Actor.h"
#include "ActorFactory.h"
#include "GameInstance.h"
#include "SDLRenderableComponent.h"
#include "Scene.h"
#include "AnimationComponent.h"

#define DLLEXP   __declspec( dllexport )

class EngineController
{
private:
	GameInstance *p_instance;
	list<StrongActorPtr> gameActors;
	StrongActorPtr selectedActor;
	Scene *p_gameScene;

	int actorIndex;

public:
	 DLLEXP EngineController();
	 DLLEXP ~EngineController();

	 DLLEXP void run();

	 DLLEXP void addActor();
	 DLLEXP void selectActor(int actorId);
	 DLLEXP void setActorTranslation(Vector2 newLocation);

	 DLLEXP bool addSDLRenderable(const char* p_fileLocation, Point2DF p_size, Point2DF p_cell);
	 DLLEXP bool addCircCollidable(float r, bool isStatic);
	 DLLEXP bool addRectCollidable(float w, float h, bool isStatic);
	 DLLEXP bool addPhysics();
	 DLLEXP bool addKeyboardInput();
	 DLLEXP bool addControllerInput();
	 DLLEXP bool addSideScrollerController();
	 DLLEXP bool addTopDownController();
	 DLLEXP bool addAnimation(const char* p_fileLocation, int totalFrames, int numberColumns, Point2DF p_size, Point2DF p_cell);
};

