// ScriptEngineConnector.cpp : main project file.

#include "stdafx.h"
#include "..\GenesisEngine\EngineController.h"

using namespace System;

public ref class ScriptEngineConnector{

	EngineController* m_engineController;

	ScriptEngineConnector::ScriptEngineConnector()
	{ 
		m_engineController = new EngineController();
	}

	ScriptEngineConnector::~ScriptEngineConnector()
	{
		if (nullptr != m_engineController)
		{
			delete m_engineController;
			m_engineController = nullptr;
		}
	}

	ScriptEngineConnector::!ScriptEngineConnector()
	{
		if (nullptr != m_engineController)
		{
			delete m_engineController;
			m_engineController = nullptr;
		}
	}

	void ScriptEngineConnector::run(){
		if (nullptr != m_engineController){
			m_engineController->run();
		}
	}

	void ScriptEngineConnector::addActor(){
		if (nullptr != m_engineController){
			m_engineController->addActor();
		}
	}

	void ScriptEngineConnector::selectActor(int id){
		if (nullptr != m_engineController){
			m_engineController->selectActor(id);
		}
	}

	void ScriptEngineConnector::setActorTranslation(Vector2 newLocation){
		if (nullptr != m_engineController){
			m_engineController->setActorTranslation(newLocation);
		}
	}

	void ScriptEngineConnector::addSDLRenderable(const char* p_fileLocation, Point2DF p_size, Point2DF p_cell){
		if (nullptr != m_engineController){
			m_engineController->addSDLRenderable(p_fileLocation, p_size, p_cell);
		}
	}

	void ScriptEngineConnector::addCircCollidable(float r, bool isStatic){
		if (nullptr != m_engineController){
			m_engineController->addCircCollidable(r, isStatic);
		}
	}

	void ScriptEngineConnector::addRectCollidable(float w, float h, bool isStatic){
		if (nullptr != m_engineController){
			m_engineController->addRectCollidable(w, h, isStatic);
		}
	}

	void ScriptEngineConnector::addPhysics(){
		if (nullptr != m_engineController){
			m_engineController->addPhysics();
		}
	}

	void ScriptEngineConnector::addKeyboardInput(){
		if (nullptr != m_engineController){
			m_engineController->addKeyboardInput();
		}
	}

	void ScriptEngineConnector::addControllerInput(){
		if (nullptr != m_engineController){
			m_engineController->addControllerInput();
		}
	}

	void ScriptEngineConnector::addSideScrollerController(){
		if (nullptr != m_engineController){
			m_engineController->addSideScrollerController();
		}
	}

	void ScriptEngineConnector::addTopDownController(){
		if (nullptr != m_engineController){
			m_engineController->addTopDownController();
		}
	}

	void ScriptEngineConnector::addAnimation(const char* p_fileLocation, int totalFrames, int numberColumns, Point2DF p_size, Point2DF p_cell){
		if (nullptr != m_engineController){
			m_engineController->addAnimation(p_fileLocation, totalFrames, numberColumns, p_size, p_cell);
		}
	}

};
