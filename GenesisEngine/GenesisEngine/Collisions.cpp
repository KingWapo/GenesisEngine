#include "Collisions.h"


Collisions::Collisions()
{
}


Collisions::~Collisions()
{
}

bool Collisions::hasCollision(Rect2D RectA, Rect2D RectB)
{

}

bool Collisions::hasCollision(Rect2D RectA, Circ2D CircB)
{
	// Check if the Circle's center is within the rect
	Vector2 circCenter = CircB.C();
	float width = (RectA.A() - RectA.B()).mag();
	float height = (RectA.B() - RectA.C()).mag();
}

bool Collisions::hasCollision(Circ2D CircA, Rect2D RectB)
{
	hasCollision(RectB, CircA);
}

bool Collisions::hasCollision(Circ2D CircA, Circ2D CircB)
{
	float distance = (CircA.C() - CircB.C()).mag();
	return distance <= abs(CircA.R() - CircB.R());
}