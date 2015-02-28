#pragma once
#include "CollidableComponent.h"
#include "Transform2dComponent.h"
#include "Vector2.h"

class RectCollidableComponent : public CollidableComponent
{
public:
	// Constructors
	RectCollidableComponent();
	RectCollidableComponent(float p_width, float p_height);
	RectCollidableComponent(Vector2 p_offset, float p_width, float p_height);

	~RectCollidableComponent() { }

	virtual bool vInit(void);
	virtual bool vUpdate(int deltaMs);
	virtual void vOnChanged(void);

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
	shared_ptr<Transform2dComponent> p_transformation;
	Vector2 m_offset;
	float height;
	float width;
};

