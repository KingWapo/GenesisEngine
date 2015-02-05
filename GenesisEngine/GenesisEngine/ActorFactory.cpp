#include "ActorFactory.h"
#include "ActorComponent.h"
#include "String.h"


// Factory class definition
ActorFactory::ActorFactory(void)
{
	m_lastActorId = INVALID_ACTOR_ID;
	
	// Register all component types
	//m_componentFactory.Register<Transform2dComponent>(ActorComponent::GetIdFromName(Transform2dComponent::g_Name));
	//m_componentFactory.Register<Renderer2dComponent>(ActorComponent::GetIdFromName(Renderer2dComponent::g_Name));

}

StrongActorPtr ActorFactory::CreateActor(const char *actorResource, TiXmlElement *overrides, /*initialTransform, */ const ActorId serversActorId)
{
	// Setup for xml
	TiXmlElement *pRoot = overrides; // Not correct

	// Create the actor instance
	ActorId nextActorId = serversActorId;
	if (nextActorId == INVALID_ACTOR_ID)
	{
		nextActorId = GetNextActorId();
	}
	StrongActorPtr pActor(GCC_NEW Actor(nextActorId));
	if (!pActor->Init(pRoot))
	{
		GCC_ERROR("Failed to initialize actor: " + std::string(actorResource));
		return StrongActorPtr();
	}

	bool initialTransformSet = false;

	// Loop through each child element and load the component
	//Xml stuff

	if (overrides)
	{
		ModifyActor(pActor, overrides);
	}

	// Set the transform component first


	pActor->PostInit();

	return pActor;
}

StrongActorComponentPtr ActorFactory::VCreateComponent(TiXmlElement *pData)
{
	// Xml stuff

	return StrongActorComponentPtr();
}

void ActorFactory::ModifyActor(StrongActorPtr pActor, TiXmlElement *overrides)
{
	// Uses xml
}