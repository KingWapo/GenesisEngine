#include "PointParticle.h"
#include "Vector2.h"
#include "Force.h"
#include "Constraint.h"

#include <math.h>
#include <vector>
#include <map>

//===================================
// CONSTRUCTORS
//===================================

/** DEFAULT CONSTRUCTOR **/
PointParticle::PointParticle() {
	position = Vector2();
	velocity = Vector2();
	mass = 0.;
	grav = 0.;
}

/** OVERLOADED CONSTRUCTOR **/
PointParticle::PointParticle(Vector2 pPosition, Vector2 pVelocity, float pMass, float pGrav) {
	setPosition(pPosition);
	setVelocity(pVelocity);
	setMass(pMass);
	setGrav(pGrav);
}

//===================================
// SETTERS
//===================================

/** SET POSITION OF PARTICLE **/
void PointParticle::setPosition(Vector2 pPosition) {
	position = pPosition;
}

/** SET VELOCITY OF PARTICLE **/
void PointParticle::setVelocity(Vector2 pVelocity) {
	velocity = pVelocity;
}

/** SET MASS OF PARTICLE **/
void PointParticle::setMass(float pMass) {
	mass = pMass;
}

/** SET LITTLE G COEFFICIENT OF PARTICLE  **/
void PointParticle::setGrav(float pGrav) {
	grav = pGrav;
}

//===================================
// GETTERS
//===================================

/** GET POSITION OF PARTICLE **/
Vector2 PointParticle::getPosition() {
	return position;
}

/** GET VELOCITY OF PARTICLE **/
Vector2 PointParticle::getVelocity() {
	return velocity;
}

/** GET MASS OF PARTICLE **/
float PointParticle::getMass() {
	return mass;
}

/** GET LITTLE G COEFFICIENT OF PARTICLE **/
float PointParticle::getGrav() {
	return grav;
}

//===================================
// HELPERS
//===================================

/** UPDATE POSITION/VELOCITY OF PARTICLE **/
void PointParticle::update(float deltaTime) {
	Vector2 netForce = this->netForce();

	float tempDt = .1f;

	switch (integration) {
	case Euler:
		euler(netForce, tempDt);
		break;
	case Verlet:
		verlet(netForce, tempDt);
		break;
	case RungeKutta4:
		rk4(netForce, tempDt);
		break;
	default:
		break;
	}
}

/** MOVE PARTICLE BY DELTA UNITS **/
void PointParticle::move(Vector2 positionDelta) {
	position += positionDelta;
}

/** ACCELERATE PARTICLE BY DELTA UNITS **/
void PointParticle::accelerate(Vector2 velocityDelta) {
	velocity += velocityDelta;
}

/** ADD FORCE TO QUEUE **/
void PointParticle::addForce(Force force) {
	forceQueue.push_back(force);
}

void PointParticle::addForce(PointParticle &particle, ForceType type) {
	Force force = Force(particle, type);

	addForce(force);
}

/** ADD CONSTRAINT TO PARTICLE **/
void PointParticle::addConstraint(PointParticle &particle, Constraint constraint) {
	constraints[particle] = constraint;
}

void PointParticle::addConstraint(PointParticle &particle, float max, float min) {
	Constraint constraint = Constraint(max, min);

	addConstraint(particle, constraint);
}

/** CALCULATE KINETIC ENERGY OF PARTICLE **/
float PointParticle::kineticEnergy() {
	float speed = getVelocity().mag();

	return (.5f * getMass() * pow(speed, 2));
}

/** CALCULATE POTENTIAL ENERGY OF PARTICLE **/
float PointParticle::potentialEnergy() {
	return getMass() * getGrav() * getPosition().y;
}

/** GRAVITATIONAL FORCE ON PARTICLE **/
Vector2 PointParticle::gravityForce(PointParticle &other) {
	Vector2 distance = getPosition() - other.getPosition();

	return ((-getGrav() * getMass() * other.getMass()) / distance.mag2()) * distance.norm();
}

/** SPRING FORCE ON PARTICLE **/
Vector2 PointParticle::springForce(PointParticle &other, float k, float l0) {
	// k is spring constant
	// l0 is equilibrium length

	Vector2 L = getPosition() - other.getPosition(); // distance between particles
	float s = l0 - L.mag(); // distance from equilibrium

	return k * s * L.norm();
}

/** EULER INTEGRATION **/
// highest speed, lowest accuracy
void PointParticle::euler(Vector2 netForce, float deltaTime) {
	move(getVelocity() * deltaTime);
	accelerate((netForce / getMass()) * deltaTime);
}

/** VERLET INTEGRATION **/
// average speed, average accuracy
void PointParticle::verlet(Vector2 netForce, float deltaTime) {
	// update position
	Vector2 movement = (getVelocity() * deltaTime);
	movement += (.5 * (netForce / getMass()) * pow(deltaTime, 2));

	move(movement);

	// set old force then update velocity
	if (forceOld == Vector2(0., 0.)) {
		forceOld = netForce;
		update(deltaTime);
	} else {
		accelerate(((netForce + forceOld) * deltaTime) / 2 * getMass());
		forceOld = Vector2(0., 0.);
	}
}

/** RUNGE KUTTA 4 INTEGRATION **/
// lowest speed, highest accuracy
void PointParticle::rk4(Vector2 netForce, float deltaTime) {
	// set changes in position and velocity
	rkPos[rkIndex] = (deltaTime / getMass()) * netForce;
	rkVel[rkIndex] = getVelocity() * deltaTime;

	// update position and velocity
	if (rkIndex == 0 || rkIndex == 1) {
		move(rkVel[rkIndex] / 2.);
		accelerate(rkPos[rkIndex] / 2.);
	} else if (rkIndex == 2) {
		move(rkVel[rkIndex]);
		accelerate(rkPos[rkIndex]);
	}

	// update index or final position and velocity
	if (rkIndex < 3) {
		rkIndex++;
		update(deltaTime);
	} else {
		Vector2 movement = ((1 / 6.f) * rkVel[0]);
		movement += (2 * rkVel[1]);
		movement += (2 * rkVel[2]);
		movement += rkVel[3];

		move(movement);

		Vector2 acceleration = ((1 / 6.f) * rkPos[0]);
		acceleration += (2 * rkPos[1]);
		acceleration += (2 * rkPos[2]);
		acceleration += rkPos[3];

		accelerate(acceleration);

		rkIndex = 0;
	}
}

/** GET SUM OF FORCES ACTING ON PARTICLE **/
Vector2 PointParticle::netForce() {
	Vector2 netForce = Vector2();

	for each (Force force in forceQueue){
		Vector2 curForce;

		switch (force.type) {
		case Gravity:
			curForce = gravityForce(force.particle);
			break;
		case Spring:
			curForce = springForce(force.particle, force.k, force.l0);
			break;
		default:
			break;
		}

		netForce += curForce;
	}

	return netForce;
}

/** FRIEND OPERATORS **/
bool operator<(const PointParticle &lhs, const PointParticle& rhs){
	return &lhs < &rhs;
}

/** ACTOR COMPONENT OVERRIDES **/
const char* PointParticle::g_Name = "PointParticle";

/*
TiXmlElement* PointParticle::VGenerateXml() {
	return NULL;
}
*/