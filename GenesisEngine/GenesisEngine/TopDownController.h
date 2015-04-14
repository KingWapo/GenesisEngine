#pragma once

#include "ActorComponent.h"
#include "Vector2.h"
#include "Transform2dComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "AnimationState.h"
#include "InputManager.h"

class TopDownController : public ActorComponent
{
public:
	TopDownController();
	~TopDownController();

	float m_moveSpeed = 1.0f;

	virtual bool vInit(void) override;
	virtual bool vUpdate(int deltaMs) override;

	static const char *g_name;
	virtual const char *VGetName() const { return g_name; }

	void initAnimations();
	void updateAnimations(float hAxis, float vAxis);

private:
	shared_ptr<Transform2dComponent> m_transform;
	shared_ptr<PhysicsComponent> m_physics;
	shared_ptr<AnimationComponent> m_animationComponent;
	shared_ptr<InputManager> m_input;
};

