#pragma once

#include "Templates.h"
#include "interfaces.h"
#include "Actor.h"

// The components
#include "Transform2dComponent.h"
#include "Renderer2dComponent.h"

// ActorFactory
class ActorFactory
{
	ActorId m_lastActorId;

protected:
	GenericObjectFactory<ActorComponent, ComponentId> m_componentFactory;

public:
	ActorFactory(void);

	StrongActorPtr CreateActor(const char *actorResource, TiXmlElement *overrides, /*initialTransform, */ const ActorId serversActorId);
	void ModifyActor(StrongActorPtr pActor, TiXmlElement *overrides);

	virtual StrongActorComponentPtr VCreateComponent(TiXmlElement *pData);

private:
	ActorId GetNextActorId(void) { ++m_lastActorId; return m_lastActorId; }
};