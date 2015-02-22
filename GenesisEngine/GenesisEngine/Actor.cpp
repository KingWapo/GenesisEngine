#include "Actor.h"
#include "ActorComponent.h"

#include <iostream>

using namespace std;

// Actor
Actor::Actor(ActorId id)
{
	m_id = id;
	m_type = "Unknown";

	m_resource = "Unknown";

	cout << "Actor Created" << endl;
}

Actor::~Actor(void)
{
	cout << "Actor id: " + m_id << endl;
	GCC_LOG("Actor", std::string("Destroying Actor ") + ToStr(m_id));
	GCC_ASSERT(m_components.empty()); // If this assert fires, the actor was destroyed without calling Actor::Destroy()
	
}

bool Actor::Init(TiXmlElement *pData)
{
	GCC_LOG("Actor", std::string("Initializing Actor ") + ToStr(m_id));

	// Setup for xml
	//m_type = pData->Attribute("type");
	//m_resource = pData->Attribute("resource");
	return true;
}

void Actor::PostInit(void)
{
	for (ActorComponents::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		it->second->vPostInit();
	}
}

void Actor::Destroy(void)
{
	// Something is wrong here?
	m_components.clear();
}

bool Actor::Update(int deltaMs)
{
	bool changed = false;
	for (ActorComponents::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		changed = changed | it->second->vUpdate(deltaMs);
	}
	return changed;
}

void Actor::Draw()
{
	for (ActorComponents::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		it->second->vDraw();
	}
}

std::string Actor::ToXML()
{
	// set up for xml
	return "Unknown";
}

void Actor::AddComponent(StrongActorComponentPtr pComponent, bool p_RenderComp)
{
	// Prof. B: Maybe it should not always take ownership?
	(*pComponent).SetOwner(StrongActorPtr(this));
	(*pComponent).vInit();

	std::pair<ActorComponents::iterator, bool> success;
	success = m_components.insert(std::make_pair(pComponent->VGetId(), pComponent));
	GCC_ASSERT(success.second);
}