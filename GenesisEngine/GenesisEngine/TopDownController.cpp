#include "TopDownController.h"

#include "Actor.h"

const char *TopDownController::g_name = "TopDownController";

TopDownController::TopDownController()
{
}


TopDownController::~TopDownController()
{
}

bool TopDownController::vInit() {
	m_transform = m_pOwner.lock()->GetComponent<Transform2dComponent>("Transform2dComponent");
	m_physics = m_pOwner.lock()->GetComponent<PhysicsComponent>("PhysicsComponent");
	m_keyboardInput = m_pOwner.lock()->GetComponent<KeyboardInput>("KeyboardInput");

	GCC_ASSERT(m_transform != nullptr);
	GCC_ASSERT(m_physics != nullptr);
	GCC_ASSERT(m_keyboardInput != nullptr);

	return true;
}

bool TopDownController::vUpdate(int deltaMs) {
	Vector2 baseSpeed = Vector2(.2f, .2f);
	float hAxis = m_keyboardInput->horizontalAxis(AxisSource::WASD);
	float vAxis = m_keyboardInput->verticalAxis(AxisSource::WASD);

	baseSpeed.x = baseSpeed.x * hAxis;
	baseSpeed.y = baseSpeed.y * vAxis;

	m_physics->setVelocity(baseSpeed);

	return true;
}