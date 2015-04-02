#pragma once

#include "Vector2.h"
#include "CollidableComponent.h"
#include "RectCollidableComponent.h"
#include "CircCollidableComponent.h"

class Collisions
{
public:
	Collisions();
	~Collisions();

	static bool hasCollision(CollidableComponent *, CollidableComponent *);
	static bool hasCollision(Rect2D, Rect2D);
	static bool hasCollision(Rect2D, Circ2D);
	static bool hasCollision(Circ2D, Rect2D);
	static bool hasCollision(Circ2D, Circ2D);

private:
	static bool checkIntersection(Circ2D, Vector2, Vector2);
	static bool checkContains(Circ2D, Vector2);
};

