#pragma once

class Constraint {
public:
	Constraint(float pMax, float pMin) {
		maxLength = pMax;
		minLength = pMin;
	};

	float maxLength;
	float minLength;
protected:
private:
};