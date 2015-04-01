#pragma once
#include "CollidableComponent.h"
#include "Transform2dComponent.h"
#include "Vector2.h"

class CircCollidableComponent : public CollidableComponent
{
public:
	CircCollidableComponent();
	CircCollidableComponent(float p_r);
	CircCollidableComponent(Circ2D p_circ, bool p_static);

	~CircCollidableComponent() { }

	virtual bool vUpdate(int deltaMs);
	virtual void vOnChanged(void);

	// Collidable interface
	virtual void onCollision() {}
	virtual void onCollisionBegin() {}
	virtual void onCollisionEnd() {}

	virtual void onOverlap() {}
	virtual void onOverlapBegin() {}
	virtual void onOverlapEnd() {}

	Circ2D getCirc() { m_circ; }
	float getRadius() { return m_circ.R(); }

	void setCirc(Circ2D p_circ) { m_circ = p_circ; }
	void setRadius(float p_r) { m_circ.setRadius(p_r); }

private:
	Circ2D m_circ;
};

