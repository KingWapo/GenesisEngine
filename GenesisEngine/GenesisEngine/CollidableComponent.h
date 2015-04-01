#pragma once
#include "Actor.h"
#include "ActorComponent.h"
#include "Transform2dComponent.h"

class CollidableComponent :	public ActorComponent
{
public:
	CollidableComponent() { }
	~CollidableComponent() { }

	virtual bool vInit(void) {
		if (m_pOwner.use_count() != 0)
		{
			StrongActorPtr l_ownerPtr = m_pOwner.lock();
			Actor* l_owner = static_cast<Actor*>(l_ownerPtr.get());
			m_transformation = l_owner->GetComponent<Transform2dComponent>("Transform2dComponent");
			if (m_transformation.get() != NULL)
			{
				return true;
			}
		}
		return false;
	}

	virtual bool vUpdate(int deltaMs) { return false; }

	virtual void vOnChanged(void) { } 

	//virtual bool isColliding(CollidableComponent other);
	//virtual void resolveCollision(CollidableComponent other);

	// Collidable interface
	virtual void onCollision() = 0;
	virtual void onCollisionBegin() = 0;
	virtual void onCollisionEnd() = 0;

	virtual void onOverlap() = 0;
	virtual void onOverlapBegin() = 0;
	virtual void onOverlapEnd() = 0;

	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	shared_ptr<Transform2dComponent> getTransform() { return m_transformation; }
	bool isStatic() { return m_isStatic; }
protected:
	shared_ptr<Transform2dComponent> m_transformation;
	bool m_isStatic;
};

