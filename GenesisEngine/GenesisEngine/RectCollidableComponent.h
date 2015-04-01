#pragma once
#include "CollidableComponent.h"
#include "ActorComponent.h"
#include "Vector2.h"

class RectCollidableComponent : public CollidableComponent
{
public:
	// Constructors
	RectCollidableComponent();
	RectCollidableComponent(Rect2D p_rect, bool p_static);

	~RectCollidableComponent() { }

	virtual bool vUpdate(int deltaMs);
	virtual void vOnChanged(void);

	// Collidable interface
	virtual void onCollision() {}
	virtual void onCollisionBegin() {}
	virtual void onCollisionEnd() {}

	virtual void onOverlap() {}
	virtual void onOverlapBegin() {}
	virtual void onOverlapEnd() {}

	Rect2D getRect() { return m_rect; }
	Transform2dComponent getTransform();

	void setRect(Rect2D p_rect){ m_rect = p_rect; }

private:
	Rect2D m_rect;

protected:
};

