#include "Transformation2d.h"

/*
	Transformation::Transformation
	Holds the location with a Vector2 and the rotation in degrees of an
	actors transformation.
*/
Transformation2d::Transformation2d()
{
	location = Vector2(0, 0);
	rotation = 0.0f;
}
/*
	Alternate constructor with given location and rotation.
*/
Transformation2d::Transformation2d(Vector2 pLocation, float pRotation)
{
	location = pLocation;
	rotation = pRotation;

	// Set rotation between 0 and 360
	while (rotation < 0)
	{
		rotation += 360;
	}
	while (rotation >= 360)
	{
		rotation -= 360;
	}
}

Transformation2d::~Transformation2d() {

}

/* 
	Transformation::SetRotation
	Sets the rotation of the actor. Automatically sets it
	between 0 and 360.
*/
void Transformation2d::SetRotation(float newRotation)
{
	rotation = newRotation;

	// Set rotation between 0 and 360
	while (rotation < 0)
	{
		rotation += 360;
	}
	while (rotation >= 360)
	{
		rotation -= 360;
	}
}