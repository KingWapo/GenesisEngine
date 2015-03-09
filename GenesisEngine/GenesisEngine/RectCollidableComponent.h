#pragma once
#include "CollidableComponent.h"
#include "ActorComponent.h"
#include "Vector2.h"

class RectCollidableComponent : public CollidableComponent
{
public:
	// Constructors
	RectCollidableComponent();
	RectCollidableComponent(float p_width, float p_height, bool p_static);
	RectCollidableComponent(Vector2 p_offset, float p_width, float p_height, bool p_static);

	~RectCollidableComponent() { }

	virtual bool vUpdate(int deltaMs);
	virtual void vOnChanged(void);

	virtual bool isColliding(RectCollidableComponent &other);
	virtual void resolveCollision(RectCollidableComponent &other);

	// Collidable interface
	virtual void onCollision() {}
	virtual void onCollisionBegin() {}
	virtual void onCollisionEnd() {}

	virtual void onOverlap() {}
	virtual void onOverlapBegin() {}
	virtual void onOverlapEnd() {}

	Rect2D getRect();
	Vector2 getSize();
	Vector2 getOffset();

	void setWidth(float p_w);
	void setHeight(float p_h);
	void setSize(float p_w, float p_h);
	void setOffset(Vector2 p_offset);

private:
	Vector2 m_offset;
	float height;
	float width;

	bool isStatic;

protected:
};

