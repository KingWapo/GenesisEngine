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
	m_animationComponent = m_pOwner.lock()->GetComponent<AnimationComponent>("AnimationComponent");
	m_input = m_pOwner.lock()->GetComponent<InputManager>("InputManager");

	GCC_ASSERT(m_transform != nullptr);
	GCC_ASSERT(m_physics != nullptr);
	GCC_ASSERT(m_input != nullptr);

	if (m_animationComponent != nullptr){
		m_animationComponent->setCurrentDirection(0);
		initAnimations();
	}

	// gravity
	m_physics->addForce(Vector2(0.0f, -.5f));

	return true;
}

bool SideScrollerController::vUpdate(int deltaMs) {
	Vector2 baseSpeed = Vector2(.5f, m_physics->getVelocity().y);
	float hAxis = m_input->horizontalAxis(AxisSource::LEFT_AXIS);

	if (m_animationComponent != nullptr){
		updateAnimations(hAxis);
	}

	baseSpeed.x = baseSpeed.x * hAxis * m_moveSpeed;

	m_physics->setVelocity(baseSpeed);

	// add check to prevent multiple jumps
	if (m_input->onKeyDown(KeyCode::SPACE) || m_input->onKeyDown(ControllerButton::A_BTN)) {
		Vector2 jumpSpeed = Vector2(m_physics->getVelocity().x, .5f);

		jumpSpeed.y = jumpSpeed.y * m_jumpHeight;

		m_physics->setVelocity(jumpSpeed);
	}

	return true;
}

void SideScrollerController::updateAnimations(float hAxis){
	if (isJumping){
		m_animationComponent->activateAnimationState("jump");
	}
	else if (isFalling){
		m_animationComponent->activateAnimationState("fall");
	}
	else if (isLanding){
		m_animationComponent->activateAnimationState("land");
	}
	else if (hAxis != 0){
		m_animationComponent->activateAnimationState("move");
	}
	else if (hAxis == 0){
		m_animationComponent->activateAnimationState("idle");
	}

	if (hAxis > 0){
		m_animationComponent->setCurrentDirection(1);
	}
	else if (hAxis < 0){
		m_animationComponent->setCurrentDirection(0);
	}
}

void SideScrollerController::initAnimations(){
	AnimationState idle("idle", 2, 0);
	AnimationState move("move", 2, 2);
	AnimationState jump("jump", 2, 7);
	AnimationState fall("fall", 2, 7);
	AnimationState land("land", 2, 7);

	idle.setDirectionAnimation(Animation(10, 10), 0);
	idle.setDirectionAnimation(Animation(30, 30), 1);
	idle.setActive(true);

	move.setDirectionAnimation(Animation(50, 59), 0);
	move.setDirectionAnimation(Animation(70, 79), 1);
	move.setActive(false);

	jump.setDirectionAnimation(Animation(50, 55), 0);
	jump.setDirectionAnimation(Animation(70, 75), 1);
	jump.setActive(false);

	fall.setDirectionAnimation(Animation(50, 59), 0);
	fall.setDirectionAnimation(Animation(70, 79), 1);
	fall.setActive(false);

	land.setDirectionAnimation(Animation(50, 59), 0);
	land.setDirectionAnimation(Animation(70, 79), 1);
	land.setActive(false);

	m_animationComponent->addAnimationState(idle);
	m_animationComponent->addAnimationState(move);
	m_animationComponent->addAnimationState(jump);
	m_animationComponent->addAnimationState(fall);
	m_animationComponent->addAnimationState(land);
}