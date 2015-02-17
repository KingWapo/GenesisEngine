#pragma once

#include "ActorComponent.h"

#include "Vector2.h"
#include "Constraint.h"

#include <vector>
#include <map>

enum IntegrationType { Euler, Verlet, RungeKutta4 };
enum ForceType { Gravity, Spring };

class Force;

class PointParticle : public ActorComponent {
public:
	// constructors
	PointParticle();
	PointParticle(Vector2 pPosition, Vector2 pVelocity, float pMass, float pGrav);

	// setters
	void setPosition(Vector2 pPosition);
	void setVelocity(Vector2 pVelocity);
	void setMass(float pMass);
	void setGrav(float pGrav);

	// getters
	Vector2 getPosition();
	Vector2 getVelocity();
	float getMass();
	float getGrav();

	// update particle
	void update(float deltaTime);
	void move(Vector2 positionDelta);
	void accelerate(Vector2 velocityDelta);

	// add forces and constraints to particle
	void addForce(Force force);
	void addForce(PointParticle &particle, ForceType type);
	void addConstraint(PointParticle &particle, Constraint constraint);
	void addConstraint(PointParticle &particle, float max, float min);

	friend bool operator<(const PointParticle &lhs, const PointParticle& rhs);

	// verlet helper variable
	Vector2 forceOld;

	// rk4 helper variables
	Vector2 rkPos[4];
	Vector2 rkVel[4];
	int rkIndex;

	// which integration does this particle use
	IntegrationType integration;

	// actor component overrides
	static const char* g_Name;
	//virtual TiXmlElement* VGenerateXml(void) override;
	virtual const char* VGetName() const { return g_Name; }
protected:
private:
	// energy of particle
	float kineticEnergy();
	float potentialEnergy();

	// forces on particle
	Vector2 gravityForce(PointParticle &other);
	Vector2 springForce(PointParticle &other, float k, float l0);

	// integration methods
	void euler(Vector2 netForce, float deltaTime);
	void verlet(Vector2 netForce, float deltaTime);
	void rk4(Vector2 netForce, float deltaTime);

	// net forces on particle
	Vector2 netForce();

	// member variables
	Vector2 position;
	Vector2 velocity;
	float mass;
	float grav;

	// forces and constraints on particle
	std::vector<Force> forceQueue;
	std::map<PointParticle, Constraint> constraints;
};