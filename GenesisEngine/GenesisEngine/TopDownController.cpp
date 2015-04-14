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
	m_input = m_pOwner.lock()->GetComponent<InputManager>("InputManager");

	GCC_ASSERT(m_transform != nullptr);
	GCC_ASSERT(m_physics != nullptr);
	GCC_ASSERT(m_input != nullptr);

	return true;
}

bool TopDownController::vUpdate(int deltaMs) {
	Vector2 baseSpeed = Vector2(.2f, .2f);
	float hAxis = m_input->horizontalAxis(AxisSource::LEFT_AXIS);
	float vAxis = m_input->verticalAxis(AxisSource::LEFT_AXIS);

	baseSpeed.x = baseSpeed.x * hAxis;
	baseSpeed.y = baseSpeed.y * vAxis;

	m_physics->setVelocity(baseSpeed);

	return true;
}