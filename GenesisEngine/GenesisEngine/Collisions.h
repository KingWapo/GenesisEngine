#pragma once

#include "Vector2.h"

class Collisions
{
public:
	Collisions();
	~Collisions();

	static bool hasCollision(Rect2D, Rect2D);
	static bool hasCollision(Rect2D, Circ2D);
	static bool hasCollision(Circ2D, Rect2D);
	static bool hasCollision(Circ2D, Circ2D);
};

