#include "SideScrollerController.h"

#include "Actor.h"

const char *SideScrollerController::g_name = "SideScrollerController";

SideScrollerController::SideScrollerController()
{
}


SideScrollerController::~SideScrollerController()
{
}

bool SideScrollerController::vInit() {
	m_transform = m_pOwner.lock()->GetComponent<Transform2dComponent>("Transform2dComponent");
	m_physics = m_pOwner.lock()->GetComponent<PhysicsComponent>("PhysicsComponent");
	m_keyboardInput = m_pOwner.lock()->GetComponent<KeyboardInput>("KeyboardInput");

	GCC_ASSERT(m_transform != nullptr);
	GCC_ASSERT(m_physics != nullptr);
	GCC_ASSERT(m_keyboardInput != nullptr);

	// gravity
	m_physics->addForce(Vector2(0.0f, -.5f));

	return true;
}

bool SideScrollerController::vUpdate(int deltaMs) {
	Vector2 baseSpeed = Vector2(.5f, m_physics->getVelocity().y);
	float hAxis = m_keyboardInput->horizontalAxis(AxisSource::WASD);

	baseSpeed.x = baseSpeed.x * hAxis * m_moveSpeed;

	m_physics->setVelocity(baseSpeed);

	// add check to prevent multiple jumps
	if (m_keyboardInput->onKeyDown(KeyCode::SPACE)) {
		Vector2 jumpSpeed = Vector2(m_physics->getVelocity().x, .5f);

		jumpSpeed.y = jumpSpeed.y * m_jumpHeight;

		m_physics->setVelocity(jumpSpeed);
	}

	return true;
}