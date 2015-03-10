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
	GCC_ASSERT(m_pOwner.use_count() != 0);

	StrongActorPtr l_ownerPtr = m_pOwner.lock();
	Actor* l_owner = static_cast<Actor*>(l_ownerPtr.get());

	m_input = l_owner->GetComponent<InputManager>("InputManager");
	m_transform = l_owner->GetComponent<Transform2dComponent>("Transform2dComponent");
	m_physics = l_owner->GetComponent<PhysicsComponent>("PhysicsComponent");

	return true;
}

bool CustomScript::vUpdate(int deltaMs) {
	GCC_ASSERT(m_input.get() != NULL);
	GCC_ASSERT(m_transform.get() != NULL);
	GCC_ASSERT(m_physics.get() != NULL);

	if (m_input->onKeyDown(KeyCode::W)) {
		m_physics->addForce(Vector2(0.0f, -0.1f));
	}
	if (m_input->onKeyDown(VK_SPACE)) {
		m_physics->accelerate(Vector2(0.0f, 0.3f));
	}

	m_physics->setVelocity(Vector2(m_input->horizontalAxis() * .2f, m_physics->getVelocity().y));

	return true;
}
