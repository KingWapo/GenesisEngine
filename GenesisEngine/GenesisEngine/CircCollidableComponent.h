#pragma once
#include "CollidableComponent.h"
#include "Transform2dComponent.h"
#include "Vector2.h"

class CircCollidableComponent : public CollidableComponent
{
public:
	CircCollidableComponent();
	CircCollidableComponent(float p_r);
	CircCollidableComponent(Vector2 p_offset, float p_r);
	~CircCollidableComponent();

	virtual bool vUpdate(int deltaMs);
	virtual void vOnChanged(void);

	// Collidable interface
	virtual void onCollision() {}
	virtual void onCollisionBegin() {}
	virtual void onCollisionEnd() {}

	virtual void onOverlap() {}
	virtual void onOverlapBegin() {}
	virtual void onOverlapEnd() {}

	Circ2D getCirc();
	Vector2 getOffset() { return m_offset; }
	float getRadius() { return m_radius; }

	void setRadius(float p_r) { m_radius = p_r; }
	void setOffset(Vector2 p_offset) { m_offset = p_offset; }

private:
	static const char *g_Name;
	float m_radius;
	Vector2 m_offset;
};

