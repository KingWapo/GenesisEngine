#include "EngineController.h"
#include <mono\metadata\assembly.h>

EngineController::EngineController()
{
	p_instance = new GameInstance();
	p_gameScene = new Scene();
	p_instance->Init();
	p_instance->setScene(p_gameScene);

	actorIndex = 0;

	MonoAssembly* myAssemblyStuffs;
}


EngineController::~EngineController()
{
	delete p_gameScene;
	delete p_instance;
}

void EngineController::run()
{
	p_instance->Run();
}

void EngineController::addActor()
{
	StrongActorPtr tempActor(new Actor(actorIndex));
	actorIndex++;
	Transform2dComponent *p_transformComp = new Transform2dComponent();
	p_transformComp->SetTranslation(Vector2(0.0f, 0.0f));
	StrongActorComponentPtr pTransformComp = StrongActorComponentPtr(p_transformComp);
	tempActor->AddComponent(pTransformComp, false);

	gameActors.push_back(tempActor);

	p_instance->AddActor(tempActor);

	selectedActor = tempActor;
}

void EngineController::selectActor(int actorId)
{
	vector<StrongActorComponentPtr>::iterator iter;
	for (list<StrongActorPtr>::iterator iter = gameActors.begin(); iter != gameActors.end(); ++iter)
	{
		if ((*iter)->GetId() == actorId)
		{
			selectedActor = (*iter);
		}
	}
}

void EngineController::setActorTranslation(Vector2 newLocation)
{
	selectedActor->GetComponent<Transform2dComponent>("Transform2dComponent")->SetTranslation(newLocation);
}

bool EngineController::addSDLRenderable(const char* p_fileLocation, Point2DF p_size, Point2DF p_cell)
{
	Point2DF location = selectedActor->GetComponent<Transform2dComponent>("Transform2dComponent")->GetTranslation().toPoint2DF();
	SDLRenderableComponent *p_renderComp = new SDLRenderableComponent(p_fileLocation,
		location, p_size, p_cell, p_instance->getWindow());
	StrongActorComponentPtr renderCompStrong = StrongActorComponentPtr(p_renderComp);
	selectedActor->AddComponent(renderCompStrong, false);

	p_gameScene->addRenderableComponent(renderCompStrong);

	return true;
}

bool EngineController::addAnimation(const char* p_fileLocation, Point2DF p_size, Point2DF p_cell)
{
	Point2DF location = selectedActor->GetComponent<Transform2dComponent>("Transform2dComponent")->GetTranslation().toPoint2DF();
	AnimationComponent *p_animComp = new AnimationComponent(p_fileLocation,
		location, p_size, p_cell, p_instance->getWindow());
	StrongActorComponentPtr pAnimComp = StrongActorComponentPtr(p_animComp);
	selectedActor->AddComponent(pAnimComp, true);

	p_gameScene->addRenderableComponent(pAnimComp);

	return true;
}

bool EngineController::addCircCollidable(float r, bool isStatic)
{
	Circ2D circ = Circ2D(selectedActor->GetComponent<Transform2dComponent>("Transform2dComponent")->GetTranslation(), r);
	CircCollidableComponent *p_circColl = new CircCollidableComponent(circ, isStatic);
	StrongActorComponentPtr pCircComp = StrongActorComponentPtr(p_circColl);
	selectedActor->AddComponent(pCircComp, false);
	return false;
}

bool EngineController::addRectCollidable(float w, float h, bool isStatic)
{
	Rect2D rect = Rect2D(selectedActor->GetComponent<Transform2dComponent>("Transform2dComponent")->GetTranslation(), w, h);
	RectCollidableComponent *p_rectColl = new RectCollidableComponent(rect, isStatic);
	StrongActorComponentPtr pRectComp = StrongActorComponentPtr(p_rectColl);
	selectedActor->AddComponent(pRectComp, false);
	return false;
}

bool EngineController::addPhysics()
{
	PhysicsComponent *p_physicsComp = new PhysicsComponent();
	StrongActorComponentPtr pPhysicsComp = StrongActorComponentPtr(p_physicsComp);
	selectedActor->AddComponent(pPhysicsComp, false);
	return true;
}

bool EngineController::addInputManager()
{
	InputManager *p_inputComp = new InputManager();
	StrongActorComponentPtr pInputComp = StrongActorComponentPtr(p_inputComp);
	selectedActor->AddComponent(pInputComp, false);
	return true;
}

bool EngineController::addSideScrollerController()
{
	SideScrollerController *p_sideScrollerComp = new SideScrollerController();
	StrongActorComponentPtr pController = StrongActorComponentPtr(p_sideScrollerComp);
	selectedActor->AddComponent(pController, false);
	return true;
}

bool EngineController::addTopDownController() {
	TopDownController *p_topDownComp = new TopDownController();
	StrongActorComponentPtr pController = StrongActorComponentPtr(p_topDownComp);
	selectedActor->AddComponent(pController, false);
	return true;
}
