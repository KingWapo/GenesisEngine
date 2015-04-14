#pragma once

#include "ActorComponent.h"
#include "Vector2.h"
#include "Transform2dComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "KeyboardInput.h"

class SideScrollerController : public ActorComponent
{
public:
	SideScrollerController();
	~SideScrollerController();

	float m_moveSpeed = 1.0f;
	float m_jumpHeight = 1.0f;

	virtual bool vInit(void) override;
	virtual bool vUpdate(int deltaMs) override;

	static const char *g_name;
	virtual const char *VGetName() const { return g_name; }

	void initAnimations();
	void updateAnimations(float hAxis);

	bool isJumping = false;
	bool isFalling = false;
	bool isLanding = false;

private:
	shared_ptr<Transform2dComponent> m_transform;
	shared_ptr<PhysicsComponent> m_physics;
	shared_ptr<KeyboardInput> m_keyboardInput;
	shared_ptr<AnimationComponent> m_animationComponent;
};

