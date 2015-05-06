#pragma once
#include "..\GenesisEngine\EngineController.h"

namespace Wrapper {
	public ref class EngineConnector
	{
	private:
		EngineController* engineController;
	public:
		EngineConnector()
		{
			engineController = new EngineController();
		};

		~EngineConnector(){
			delete engineController;
			engineController = NULL;
		}

		void addActor(){
			engineController->addActor();
		};

		void selectActor(int actorId){
			engineController->selectActor(actorId);
		};

		void setActorTranslation(Vector2 newLocation){
			engineController->setActorTranslation(newLocation);
		};

		bool addSDLRenderable(const char* p_fileLocation, Point2DF p_size, Point2DF p_cell){
			return engineController->addSDLRenderable(p_fileLocation, p_size, p_cell);
		};

		bool addCircCollidable(float r, bool isStatic){
			return engineController->addCircCollidable(r, isStatic);
		};

		bool addRectCollidable(float w, float h, bool isStatic){
			return engineController->addRectCollidable(w, h, isStatic);
		};

		bool addPhysics(){
			return engineController->addPhysics();
		};

		bool addKeyboardInput(){
			return engineController->addKeyboardInput();
		};

		bool addControllerInput(){
			return engineController->addControllerInput();
		};

		bool addSideScrollerController(){
			return engineController->addSideScrollerController();
		};

		bool addTopDownController(){
			return engineController->addTopDownController();
		};

		bool addAnimation(const char* p_fileLocation, int totalFrames, int numberColumns, Point2DF p_size, Point2DF p_cell){
			return engineController->addAnimation(p_fileLocation, totalFrames, numberColumns, p_size, p_cell);
		};

	};
}

