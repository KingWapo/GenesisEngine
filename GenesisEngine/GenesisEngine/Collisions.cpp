#include "Collisions.h"


Collisions::Collisions()
{
}


Collisions::~Collisions()
{
}

bool Collisions::hasCollision(CollidableComponent *colA, CollidableComponent *colB) {
	RectCollidableComponent *rectA, *rectB;
	CircCollidableComponent *circA, *circB;

	printf("\n\t"); fflush(stdout);

	switch (colA->getColType()) {
		case ColliderType::Rect:
			rectA = dynamic_cast<RectCollidableComponent*>(colA);

			switch (colB->getColType()) {
			case ColliderType::Rect:
				printf("===RECT RECT==="); fflush(stdout);
				rectB = dynamic_cast<RectCollidableComponent*>(colB);
				return hasCollision(rectA->getRect(), rectB->getRect());
				break;
			case ColliderType::Circ:
				printf("===RECT CIRC==="); fflush(stdout);
				circB = dynamic_cast<CircCollidableComponent*>(colB);
				return hasCollision(rectA->getRect(), circB->getCirc());
				break;
			}

			break;
		case ColliderType::Circ:
			circA = dynamic_cast<CircCollidableComponent*>(colA);

			switch (colB->getColType()) {
			case ColliderType::Rect:
				printf("===RECT CIRC==="); fflush(stdout);
				rectB = static_cast<RectCollidableComponent*>(colB);
				return hasCollision(rectB->getRect(), circA->getCirc());
				break;
			case ColliderType::Circ:
				printf("===CIRC CIRC==="); fflush(stdout);
				circB = static_cast<CircCollidableComponent*>(colB);
				return hasCollision(circA->getCirc(), circB->getCirc());
				break;
			}

			break;
	}

	printf("===NO COLLIDER==="); fflush(stdout);
	return false;
}

bool Collisions::hasCollision(Rect2D RectA, Rect2D RectB)
{
	Vector2 Axis[4];

	Axis[0].x = RectA.CVert().x - RectA.BVert().x;
	Axis[0].y = RectA.CVert().y - RectA.BVert().y;
	Axis[1].x = RectA.CVert().x - RectA.DVert().x;
	Axis[1].y = RectA.CVert().y - RectA.DVert().y;
	Axis[2].x = RectB.BVert().x - RectB.AVert().x;
	Axis[2].y = RectB.BVert().y - RectB.AVert().y;
	Axis[3].x = RectB.BVert().x - RectB.CVert().x;
	Axis[3].y = RectB.BVert().y - RectB.CVert().y;

	for (int i = 0; i < 4; i++)
	{
		float minA, maxA, minB, maxB, temp;
		Vector2 curAxis = Axis[i];

		// Find min and max for RectA
		minA = projection(RectA.AVert(), curAxis).dot(curAxis);
		maxA = minA;

		// Check if B is a max or min for RectA
		temp = projection(RectA.BVert(), curAxis).dot(curAxis);
		if (temp < minA)
			minA = temp;
		else if (temp > maxA)
			maxA = temp;

		// Check if C is a max or min for RectA
		temp = projection(RectA.CVert(), curAxis).dot(curAxis);
		if (temp < minA)
			minA = temp;
		else if (temp > maxA)
			maxA = temp;

		// Check if D is a max or min for RectA
		temp = projection(RectA.DVert(), curAxis).dot(curAxis);
		if (temp < minA)
			minA = temp;
		else if (temp > maxA)
			maxA = temp;

		// Find min or max for RectB
		minB = projection(RectB.AVert(), curAxis).dot(curAxis);
		maxB = minB;

		// Check if B is a max or min for RectB
		temp = projection(RectB.BVert(), curAxis).dot(curAxis);
		if (temp < minB)
			minB = temp;
		else if (temp > maxB)
			maxB = temp;

		// Check if C is a max or min for RectB
		temp = projection(RectB.CVert(), curAxis).dot(curAxis);
		if (temp < minB)
			minB = temp;
		else if (temp > maxB)
			maxB = temp;

		// Check if D is a max or min for RectB
		temp = projection(RectB.DVert(), curAxis).dot(curAxis);
		if (temp < minB)
			minB = temp;
		else if (temp > maxB)
			maxB = temp;

		// Check for absence of overlap.
		// If there's no overlap, than there cannot be
		// a collision. Therefore return false. If there
		// is an overlap on all axes, then return true.
		if (minB > maxA ||
			maxB < minA)
		{
			return false;
		}
	}

	// Made it through forloop without finding an 
	// axis that the rectangles DON'T overlap on.
	// There is a collision.
	return true;

}

Vector2 Collisions::projection(Vector2 p_point, Vector2 p_axis)
{
	return (p_point.dot(p_axis) / p_axis.mag2()) * p_axis;
}


/*	Adam - 4/1/2015
	
	Detecting collision between a circle and a rectangle

	There are 8 different zones that the circle can exist in.
			|				|
		B	|		BC		|	C
	________|_______________|________
			|B			   C|
			|				|
		AB	|		.		|	CD
			|				|
	________|A_____________D|________
			|				|
		A	|		AD		|	D
			|				|

	The following checks will determine what zone
	the circle exists in and then find if the 
	circle intersects the line segment or vert of
	that zone.

	The single letter zones will only check if the
	corresponding vertice is within the circle,
	otherwise, it will use the corresponding
	line segment and determine if it intersects
	the circle.
*/
bool Collisions::hasCollision(Rect2D RectA, Circ2D CircB)
{
	// Quick checks to finish early
	Vector2 circCenter = CircB.C();
	Vector2 rectCenter = RectA.getCenter();
	
	// Distance between centers is less than the circle's radius
	float distance = (circCenter - RectA.getCenter()).mag();
	if (distance <= CircB.R())
	{
		return true;
	}

	// Check if center is in the bounds of the rectangle
	if (circCenter.x >= RectA.AVert().x // Right of the left most edge of the Rect
		&& circCenter.x <= RectA.DVert().x // Left of the right most edge of the Rect
		&& circCenter.y >= RectA.AVert().y // Up from the lowest most edge of the Rect
		&& circCenter.y <= RectA.BVert().y // Down from the highest most edge of the Rect
		)
	{
		return true;
	}

	// More advanced checks
	float xZone = circCenter.x - rectCenter.x;
	float yZone = circCenter.y - rectCenter.y;

	// "tolerance" determines if the circ is within the x, y bounds
	// of the rect, thus ending up in an "edge" zone rather than a
	// "corner" zone.
	Vector2 tolerance = Vector2(RectA.getWidth() / 2, RectA.getHeight() / 2);

	// Circ is down and left of the rect.
	// Possible zones: A, AB, AD
	if (xZone <= 0 && yZone <= 0)
	{
		// It must be in zone AD
		if (abs(xZone) < tolerance.x)
		{
			return checkIntersection(CircB, RectA.AVert(), RectA.DVert());
		}
		// It must be in zone AB
		else if (abs(yZone) < tolerance.y) 
		{
			return checkIntersection(CircB, RectA.AVert(), RectA.BVert());
		}
		// It must be in zone A
		else
		{
			return checkContains(CircB, RectA.AVert());
		}
	}
	// Circ is up and left of the rect.
	// Possible zones B, AB, BC
	else if (xZone <= 0 && yZone >= 0)
	{
		// It must be in zone BC
		if (abs(xZone) < tolerance.x)
		{
			return checkIntersection(CircB, RectA.BVert(), RectA.CVert());
		}
		// It must be in zone AB
		else if (abs(yZone) < tolerance.y)
		{
			return checkIntersection(CircB, RectA.AVert(), RectA.BVert());
		}
		// It must be in zone B
		else
		{
			return checkContains(CircB, RectA.BVert());
		}
	}
	// Circ is up and right of the rect.
	// Possible zones C, BC, CD
	else if (xZone >= 0 && yZone >= 0)
	{
		// It must be in zone BC
		if (abs(xZone) < tolerance.x)
		{
			return checkIntersection(CircB, RectA.BVert(), RectA.CVert());
		}
		// It must be in zone CD
		else if (abs(yZone) < tolerance.y)
		{
			return checkIntersection(CircB, RectA.CVert(), RectA.DVert());
		}
		// It must be in zone C
		else
		{
			return checkContains(CircB, RectA.CVert());
		}
	}
	// Circ is down and right of the rect.
	// Possible zones D, AD, CD
	else if (xZone >= 0 && yZone <= 0)
	{
		// It must be in zone AD
		if (abs(xZone) < tolerance.x)
		{
			return checkIntersection(CircB, RectA.AVert(), RectA.DVert());
		}
		// It must be in zone CD
		else if (abs(yZone) < tolerance.y)
		{
			return checkIntersection(CircB, RectA.CVert(), RectA.DVert());
		}
		// It must be in zone D
		else
		{
			return checkContains(CircB, RectA.DVert());
		}
	}

	// Should only get here if the circle is within
	// the rect and somehow failed the previous check.
	// Return true
	return true;
}

bool Collisions::hasCollision(Circ2D CircA, Circ2D CircB)
{
	float distance = (CircA.C() - CircB.C()).mag();
	return distance <= abs(CircA.R() + CircB.R());
}

bool Collisions::checkIntersection(Circ2D CircA, Vector2 EndpointB, Vector2 EndpointC)
{
	Vector2 endToEnd = EndpointB - EndpointC;
	Vector2 circToEnd = EndpointB - CircA.C();

	float a = endToEnd.dot(endToEnd);
	float b = 2 * circToEnd.dot(endToEnd);
	float c = circToEnd.dot(circToEnd) - CircA.R() * CircA.R();

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0){
		// no intersection
		return false;
	}

	discriminant = sqrt(discriminant);

	float t1 = (-b - discriminant) / (2 * a);
	float t2 = (-b + discriminant) / (2 * a);

	if (t1 >= 0 && t1 <= 1) {
		// impale, poke
		return true;
	}

	if (t2 >= 0 && t2 <= 1) {
		// exit wound
		return true;
	}

	// fall short, past, completely inside
	return false;
}

bool Collisions::checkContains(Circ2D CircA, Vector2 VertB)
{
	float distance = (CircA.C() - VertB).mag();
	return distance <= abs(CircA.R());
}

void Collisions::resolveCollision(CollidableComponent *colA, CollidableComponent *colB) {
	shared_ptr<Transform2dComponent> tA = colA->getOwner().lock()->GetComponent<Transform2dComponent>("Transform2dComponent");
	shared_ptr<Transform2dComponent> tB = colB->getOwner().lock()->GetComponent<Transform2dComponent>("Transform2dComponent");

	Vector2 direction = (tA->GetTranslation() - tB->GetTranslation()).norm();

	if (!colA->isStatic()) {
		tA->GetTranslation() += direction;
	}

	if (!colB->isStatic()) {
		tB->GetTranslation() -= direction;
	}
}