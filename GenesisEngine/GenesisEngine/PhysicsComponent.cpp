#include "PhysicsComponent.h"
#include "Actor.h"

#include <math.h>

const char* PhysicsComponent::g_Name = "PhysicsComponent";

PhysicsComponent::PhysicsComponent() {
	setPosition(Vector2(0.0, 0.0));
	setVelocity(Vector2(0.0, 0.0));
	setMass(1.0);
	setGrav(1.0);
}

PhysicsComponent::PhysicsComponent(Vector2 p_position, Vector2 p_velocity, float p_mass, float p_grav) {
	setPosition(p_position);
	setVelocity(p_velocity);
	setMass(p_mass);
	setGrav(p_grav);
}

PhysicsComponent::~PhysicsComponent() {
}

Vector2 PhysicsComponent::netForce() {
	Vector2 netForce = Vector2();

	for each (Vector2 force in forceQueue) {
		netForce += force;
	}

	return netForce;
}

void PhysicsComponent::move(Vector2 deltaPos) {
	m_position += deltaPos;
}

void PhysicsComponent::accelerate(Vector2 deltaVel) {
	m_velocity += deltaVel;
}

void PhysicsComponent::addForce(Vector2 force) {
	forceQueue.push_back(force);
}

float PhysicsComponent::kineticEnergy() {
	float speed = getVelocity().mag();

	return (.5f * getMass() * pow(speed, 2));
}

float PhysicsComponent::potentialEnergy() {
	return getMass() * getGrav() * getPosition().y;
}

void PhysicsComponent::euler(Vector2 netForce, float deltaTime) {
	move(getVelocity() * deltaTime);
	accelerate((netForce / getMass()) * deltaTime);
}

bool PhysicsComponent::vUpdate(int deltaMs) {
	GCC_ASSERT(m_transform.get() != NULL);

	Vector2 net = netForce();

	float deltaTime = deltaMs * 1.0f;
	printf("DeltaTime: %f\n", deltaTime); fflush(stdout);

	euler(net, deltaTime);

	m_transform->SetLocation(m_position);
	return true;
}

bool PhysicsComponent::vInit() {
	GCC_ASSERT(m_pOwner.get() != NULL);

	Actor* l_owner = static_cast<Actor*>(m_pOwner.get());

	m_transform = l_owner->GetComponent<Transform2dComponent>("Transform2dComponent");

	return true;
}