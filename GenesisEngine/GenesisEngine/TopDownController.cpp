#include "TopDownController.h"
#include <iostream>

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
	m_animationComponent = m_pOwner.lock()->GetComponent<AnimationComponent>("AnimationComponent");
	m_input = m_pOwner.lock()->GetComponent<InputManager>("InputManager");

	GCC_ASSERT(m_transform != nullptr);
	GCC_ASSERT(m_physics != nullptr);
	GCC_ASSERT(m_input != nullptr);

	if (m_animationComponent != nullptr){
		m_animationComponent->setCurrentDirection(3);
		initAnimations();
	}

	return true;
}

bool TopDownController::vUpdate(int deltaMs) {
	Vector2 baseSpeed = Vector2(.2f, .2f);
	float hAxis = m_input->horizontalAxis(AxisSource::LEFT_AXIS);
	float vAxis = m_input->verticalAxis(AxisSource::LEFT_AXIS);

	if (m_animationComponent != nullptr){
		updateAnimations(hAxis, vAxis);
	}

	baseSpeed.x = baseSpeed.x * hAxis;
	baseSpeed.y = baseSpeed.y * vAxis;

	m_physics->setVelocity(baseSpeed);

	return true;
}

void TopDownController::updateAnimations(float hAxis, float vAxis){
	if (vAxis == 0 && hAxis == 0){
		m_animationComponent->activateAnimationState("idle");
	}
	else{
		m_animationComponent->activateAnimationState("move");
	}

	if (vAxis > 0){
		m_animationComponent->setCurrentDirection(2);
	}
	else if (vAxis < 0){
		m_animationComponent->setCurrentDirection(3);
	}
	else if (hAxis > 0){
		m_animationComponent->setCurrentDirection(1);
	}
	else if (hAxis < 0){
		m_animationComponent->setCurrentDirection(0);
	}
}

void TopDownController::initAnimations(){
	AnimationState idle("idle", 4, 0);
	AnimationState move("move", 4, 5);

	idle.setDirectionAnimation(Animation(10, 10), 0);
	idle.setDirectionAnimation(Animation(30, 30), 1);
	idle.setDirectionAnimation(Animation(20, 20), 2);
	idle.setDirectionAnimation(Animation(0, 0), 3);
	idle.setActive(true);

	move.setDirectionAnimation(Animation(50, 59), 0);
	move.setDirectionAnimation(Animation(70, 79), 1);
	move.setDirectionAnimation(Animation(60, 69), 2);
	move.setDirectionAnimation(Animation(40, 49), 3);
	move.setActive(false);

	m_animationComponent->addAnimationState(idle);
	m_animationComponent->addAnimationState(move);
}