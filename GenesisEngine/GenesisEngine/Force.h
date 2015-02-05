#pragma once

#include "PointParticle.h"
#include "Vector2.h"

class Force {
public:
	Force(PointParticle &pParticle, ForceType pType) {
		particle = pParticle;
		type = pType;
	};

	PointParticle particle;
	ForceType type;

	// spring force variables
	// unused for gravitational force
	float k; // spring constant
	float l0; // equilibrium length
protected:
private:
};