#include "PhysicsComponent.h"
#include "Actor.h"

#include <math.h>

const char *PhysicsComponent::g_Name = "PhysicsComponent";

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

	for (unsigned int i = 0; i < forceQueue.size(); i++) {
		netForce += forceQueue[i];
	}

	return netForce;
}

void PhysicsComponent::move(Vector2 deltaPos) {
	Vector2 newPos = m_transform->GetTranslation() + deltaPos;
	newPos.x = max(0.0f, min(1.0f, newPos.x));
	newPos.y = max(0.0f, min(.921f, newPos.y));
	m_transform->SetTranslation(newPos);
}

void PhysicsComponent::accelerate(Vector2 deltaVel) {
	m_velocity += deltaVel;
}

void PhysicsComponent::addForce(Vector2 force) {
	forceQueue.push_back(force);
}

void PhysicsComponent::clearForces() {
	forceQueue.clear();
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

	float deltaTime = deltaMs / 1000.0f;
	//printf("DeltaTime: %f\n", deltaTime); fflush(stdout);

	euler(net, deltaTime);

	//m_transform->SetTranslation(m_position);
	return true;
}

bool PhysicsComponent::vInit() {
	GCC_ASSERT(m_pOwner.use_count() != 0);

	StrongActorPtr l_ownerPtr = m_pOwner.lock();
	Actor* l_owner = static_cast<Actor*>(l_ownerPtr.get());

	m_transform = l_owner->GetComponent<Transform2dComponent>("Transform2dComponent");

	return true;
}