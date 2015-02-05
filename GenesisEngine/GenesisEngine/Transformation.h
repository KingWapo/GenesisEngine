#pragma once

#include "Vector2.h"

class Transformation2d
{
private:
	Vector2		location;
	float		rotation;

public:
	Transformation2d();
	Transformation2d(Vector2 pLocation, float pRotation);
	~Transformation2d();

	Vector2 GetLocation() const { return location; }
	void SetLocation(Vector2 newLocation) { location = newLocation; }

	float GetRotation() const { return rotation; }
	void SetRotation(float newRotation);

};