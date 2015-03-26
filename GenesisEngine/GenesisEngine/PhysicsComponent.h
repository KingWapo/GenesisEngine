#pragma once

#include "ActorComponent.h"
#include "Vector2.h"

#include "Transform2dComponent.h"

#include <vector>

class PhysicsComponent : public ActorComponent
{
public:
	PhysicsComponent();
	PhysicsComponent(Vector2 p_position, Vector2 p_velocity, float p_mass, float p_grav);

	~PhysicsComponent();

	// setters
	void setPosition(Vector2 p_position) { m_position = p_position; }
	void setVelocity(Vector2 p_velocity) { m_velocity = p_velocity; }
	void setMass(float p_mass) { m_mass = p_mass; }
	void setGrav(float p_grav) { m_grav = p_grav; }

	// getters
	Vector2 getPosition() { return m_position; }
	Vector2 getVelocity() { return m_velocity; }
	float getMass() { return m_mass; }
	float getGrav() { return m_grav; }

	// update component
	void move(Vector2 deltaPos);
	void accelerate(Vector2 deltaVel);

	// add forces
	void addForce(Vector2 force);
	void clearForces();

	// actor overrides
	virtual const char* VGetName() const { return g_Name; }
	virtual bool vInit() override;
	virtual bool vUpdate(int deltaMs) override;

private:
	static const char *g_Name;

	// properties
	Vector2 m_position;
	Vector2 m_velocity;
	float m_mass;
	float m_grav;

	shared_ptr<Transform2dComponent> m_transform;

	// energy
	float kineticEnergy();
	float potentialEnergy();

	// net force
	Vector2 netForce();

	// integration
	void euler(Vector2 netForce, float deltaTime);

	// forces on component
	std::vector<Vector2> forceQueue;
};

