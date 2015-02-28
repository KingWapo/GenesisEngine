#pragma once
#include "Actor.h"
#include "ActorComponent.h"
class CollidableComponent :	public ActorComponent
{
public:
	CollidableComponent() { }
	~CollidableComponent() { }

	virtual bool vInit(void) { return true; }
	virtual bool vUpdate(int deltaMs) { return false; }
	virtual void vOnChanged(void) { } 

	// Collidable interface
	virtual void onCollision() = 0;
	virtual void onCollisionBegin() = 0;
	virtual void onCollisionEnd() = 0;

	virtual void onOverlap() = 0;
	virtual void onOverlapBegin() = 0;
	virtual void onOverlapEnd() = 0;
};

