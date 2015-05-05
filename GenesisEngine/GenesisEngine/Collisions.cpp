#include "Collisions.h"
#include "SideScrollerController.h"


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
				//printf("===RECT RECT==="); fflush(stdout);
				rectB = dynamic_cast<RectCollidableComponent*>(colB);
				return hasCollision(rectA->getRect(), rectB->getRect());
				break;
			case ColliderType::Circ:
				//printf("===RECT CIRC==="); fflush(stdout);
				circB = dynamic_cast<CircCollidableComponent*>(colB);
				return hasCollision(rectA->getRect(), circB->getCirc());
				break;
			}

			break;
		case ColliderType::Circ:
			circA = dynamic_cast<CircCollidableComponent*>(colA);

			switch (colB->getColType()) {
			case ColliderType::Rect:
				//printf("===RECT CIRC==="); fflush(stdout);
				rectB = static_cast<RectCollidableComponent*>(colB);
				return hasCollision(rectB->getRect(), circA->getCirc());
				break;
			case ColliderType::Circ:
				//printf("===CIRC CIRC==="); fflush(stdout);
				circB = static_cast<CircCollidableComponent*>(colB);
				return hasCollision(circA->getCirc(), circB->getCirc());
				break;
			}

			break;
	}

	printf("===NO COLLIDER==="); fflush(stdout);
	return false;
}

bool Collisions::AABB(Rect2D RectA, Rect2D RectB)
{
	float xMinA = RectA.AVert().x;
	float xMinB = RectB.AVert().x;
	float xMaxA = RectA.DVert().x;
	float xMaxB = RectB.DVert().x;
	float yMinA = RectA.AVert().y;
	float yMinB = RectB.AVert().y;
	float yMaxA = RectA.BVert().y;
	float yMaxB = RectB.BVert().y;

	if (xMinA > xMaxB ||
		xMaxA < xMinB ||
		yMinA > yMaxB ||
		yMaxA < yMinB)
		return false;
		
	return true;
}

bool Collisions::hasCollision(Rect2D RectA, Rect2D RectB)
{
	Rect2D RectA_AABB, RectB_AABB;

	Vector2 a_center, b_center;
	float a_maxX, a_maxY, b_maxX, b_maxY;

	a_center = RectA.getCenter();
	b_center = RectB.getCenter();
	a_maxX = max(fabs(RectA.AVert().x - RectA.getCenter().x),
			 max(fabs(RectA.BVert().x - RectA.getCenter().x),
			 max(fabs(RectA.CVert().x - RectA.getCenter().x),
				 fabs(RectA.DVert().x - RectA.getCenter().x))));
	a_maxY = max(fabs(RectA.AVert().y - RectA.getCenter().y),
			 max(fabs(RectA.BVert().y - RectA.getCenter().y),
			 max(fabs(RectA.CVert().y - RectA.getCenter().y),
				 fabs(RectA.DVert().y - RectA.getCenter().y))));
	b_maxX = max(fabs(RectB.AVert().x - RectB.getCenter().x),
			 max(fabs(RectB.BVert().x - RectB.getCenter().x),
			 max(fabs(RectB.CVert().x - RectB.getCenter().x),
				 fabs(RectB.DVert().x - RectB.getCenter().x))));
	b_maxY = max(fabs(RectB.AVert().y - RectB.getCenter().y),
			 max(fabs(RectB.BVert().y - RectB.getCenter().y),
			 max(fabs(RectB.CVert().y - RectB.getCenter().y),
				 fabs(RectB.DVert().y - RectB.getCenter().y))));

	RectA_AABB = Rect2D(a_center, a_maxX * 2, a_maxY * 2);
	RectB_AABB = Rect2D(b_center, b_maxX * 2, b_maxY * 2);

	if (!AABB(RectA_AABB, RectB_AABB))
	{
		return false;
	}/*
	else if (RectA.rotation == 0 && RectB.rotation == 0) // they are axis - aligned
	{
		return true;
	}
	 */
	
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
	return distance <= CircA.R() + CircB.R();
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

	PhysicsComponent *A_comp = colA->getOwner().lock()->GetComponent<PhysicsComponent>("PhysicsComponent").get();
	PhysicsComponent *B_comp = colB->getOwner().lock()->GetComponent<PhysicsComponent>("PhysicsComponent").get();

	if (colA->getOwner().lock()->GetComponent<SideScrollerController>("SideScrollerController") != nullptr) {
		tA->SetTranslation(Vector2(.1f, .6f));
		A_comp->setVelocity(Vector2(.5f, 0));
	}

	//RectCollidableComponent *rectA, *rectB;
	//CircCollidableComponent *circA, *circB;

	/*Vector2 minDist;
	Vector2 actDist;

	switch (colA->getColType()) {
	case ColliderType::Rect:
		rectA = dynamic_cast<RectCollidableComponent*>(colA);
		minDist = Vector2(rectA->getRect().getWidth() / 2, rectA->getRect().getHeight() / 2);

		break;
	case ColliderType::Circ:
		circA = dynamic_cast<CircCollidableComponent*>(colA);
		minDist = (tA->GetTranslation() - tB->GetTranslation()).norm() * circA->getRadius();

		break;
	}

	switch (colB->getColType()) {
	case ColliderType::Rect:
		rectB = dynamic_cast<RectCollidableComponent*>(colB);
		minDist += Vector2(rectB->getRect().getWidth() / 2, rectB->getRect().getHeight() / 2);

		break;
	case ColliderType::Circ:
		circB = dynamic_cast<CircCollidableComponent*>(colB);
		minDist += (tA->GetTranslation() - tB->GetTranslation()).norm() * circB->getRadius();

		break;
	}

	actDist = tA->GetTranslation() - tB->GetTranslation();

	Vector2 overlap = minDist - actDist;

	if (overlap.x > overlap.y) {
		overlap.y = 0.0f;
	}
	else {
		overlap.x = 0.0f;
	}

	if (overlap.mag() > .1f) {
		if (!colA->isStatic()) {
			tA->SetTranslation(tA->GetTranslation() - overlap / 4);
		}

		if (!colB->isStatic()) {
			tB->SetTranslation(tB->GetTranslation() + overlap / 4);
		}
	}*/

	// Determine velocities based on the Physics Comp
	// or zero, if there is no Physics Comp.
	Vector2 aVel = A_comp != nullptr ? A_comp->getVelocity() : Vector2(0, 0);
	Vector2 bVel = B_comp != nullptr ? B_comp->getVelocity() : Vector2(0, 0);

	float aMass = A_comp != nullptr ? A_comp->getMass() : 1000.0f;
	float bMass = B_comp != nullptr ? B_comp->getMass() : 1000.0f;

	// Calculate relative velocity
	Vector2 relVel = bVel - aVel;

	//Calculate the collision normal
	Vector2 normal = Vector2(0, 0);
	normal = (tB->GetTranslation() - tA->GetTranslation()).norm();

	Vector2 leftNorm = Vector2(-1.0f, 0.0f);
	Vector2 rightNorm = Vector2(1.0f, 0.0f);
	Vector2 upNorm = Vector2(0.0f, 1.0f);
	Vector2 downNorm = Vector2(0.0f, -1.0f);

	if (colB->getColType() == ColliderType::Rect)
	{
		RectCollidableComponent *rectColB = dynamic_cast<RectCollidableComponent*>(colB);
		Rect2D rectB = rectColB->getRect();
		leftNorm = ((rectB.AVert() + rectB.BVert()) * 0.5f - rectB.getCenter()).norm();
		rightNorm = ((rectB.CVert() + rectB.DVert()) * 0.5f - rectB.getCenter()).norm();
		upNorm = ((rectB.BVert() + rectB.CVert()) * 0.5f - rectB.getCenter()).norm();
		downNorm = ((rectB.AVert() + rectB.DVert()) * 0.5f - rectB.getCenter()).norm();
	}

	if (fabs(normal.x) > fabs(normal.y)) // Left or right
	{
		if (normal.x > 0)
		{
			normal = rightNorm;
		}
		else
		{
			normal = leftNorm;
		}
	}
	else if (fabs(normal.y) > fabs(normal.x)) // Up or down
	{
		if (normal.y > 0)
		{
			normal = upNorm;
		}
		else
		{
			normal = downNorm;
		}
	}

	// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = relVel.dot(normal);

	// Do not resolve if velocities are separating
	if (velAlongNormal > 0)
		return;

	// Calculate restitution
	float e = 0; // Grab restitution from PhysicsComp?

	// Calculate impulse scalar
	float j = -(1 + e) * velAlongNormal;
	j /= 1 / aMass + 1 / bMass;

	// Apply impulse
	Vector2 impulse = j * normal;
	Vector2 newAVel = aVel - 1 / aMass * impulse;
	Vector2 newBVel = bVel + 1 / bMass * impulse;

	if (A_comp != nullptr)
	{
		A_comp->setVelocity(newAVel);
	}
	if (B_comp != nullptr)
	{
		B_comp->setVelocity(newBVel);
	}
}