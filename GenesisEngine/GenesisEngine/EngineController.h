#pragma once
#include "EngineCode.h"
#include "TestGame.h"
#include "InputManager.h"
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


class EngineController
{
private:
	GameInstance *p_instance;
	list<StrongActorPtr> gameActors;
	StrongActorPtr selectedActor;
	Scene *p_gameScene;

	int actorIndex;

public:
	EngineController();
	~EngineController();

	void run();

	void addActor();
	void selectActor(int actorId);
	void setActorTranslation(Vector2 newLocation);

	bool addSDLRenderable(const char* p_fileLocation, Point2DF p_size, Point2DF p_cell);
	bool addCircCollidable(float r, bool isStatic);
	bool addRectCollidable(float w, float h, bool isStatic);
	bool addPhysics();
	bool addInputManager();
	bool addSideScrollerController();
	bool addTopDownController();
	bool addAnimation(const char* p_fileLocation, Point2DF p_size, Point2DF p_cell);
};

