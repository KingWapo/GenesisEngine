#include "CustomScript.h"
#include "Actor.h"

#include <memory>
#include <iostream>
#include <Windows.h>

const char* CustomScript::g_Name = "CustomScript";

CustomScript::CustomScript()
{
}


CustomScript::~CustomScript()
{
}

bool CustomScript::vInit() {
	GCC_ASSERT(m_pOwner.get() != NULL);

	Actor* l_owner = static_cast<Actor*>(m_pOwner.get());

	m_input = l_owner->GetComponent<InputManager>("InputManager").lock();
	m_transform = l_owner->GetComponent<Transform2dComponent>("Transform2dComponent").lock();
	//m_physics = l_owner->GetComponent<PhysicsComponent>("PhysicsComponent").lock();

	return true;
}

bool CustomScript::vUpdate(int deltaMs) {
	GCC_ASSERT(m_input.get() != NULL);
	GCC_ASSERT(m_transform.get() != NULL);
	//GCC_ASSERT(m_physics.get() != NULL);

	if (m_input->onKeyDown(VK_SPACE)) {
		//m_physics->addForce(Vector2(1.0, -0.5));
	}

	m_transform->move(m_input->horizontalAxis() * 1.0f, m_input->verticalAxis() * 1.0f);

	return true;
}
