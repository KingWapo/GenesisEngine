#pragma once
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

	void addActor();
	void selectActor(int actorId);

	bool addSDLRenderable(const char* p_fileLocation, Point2DF p_size, Point2DF p_cell);
	bool addCircCollidable();
	bool addRectCollidable(float width, float height, bool isStatic);
	bool addPhysics();
	bool addInputManager();
	bool addCustomScript();
};

