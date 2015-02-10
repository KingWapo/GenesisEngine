#pragma once

class Constraint {
public:
	Constraint() {
		maxLength = 0;
		minLength = 0;
	};

	Constraint(float pMax, float pMin) {
		maxLength = pMax;
		minLength = pMin;
	};

	float maxLength;
	float minLength;
protected:
private:
};