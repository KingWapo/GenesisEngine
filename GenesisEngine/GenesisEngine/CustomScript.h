#pragma once

#include "ActorComponent.h"
#include "KeyboardInput.h"
#include "Transform2dComponent.h"
#include "PhysicsComponent.h"

class CustomScript : public ActorComponent
{
public:
	CustomScript();
	~CustomScript();

	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	virtual bool vInit(void) override;
	virtual bool vUpdate(int deltaMs) override;

private:
	shared_ptr<KeyboardInput> m_input;
	shared_ptr<Transform2dComponent> m_transform;
	shared_ptr<PhysicsComponent> m_physics;
};

