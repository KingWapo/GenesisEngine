#pragma once

#include "interfaces.h"
#include "String.h"

class TiXmlElement;

// Actor Component class
class ActorComponent
{
	friend class ActorFactory;

protected:
	StrongActorPtr m_pOwner;

public:
	virtual ~ActorComponent(void) { m_pOwner.reset(); }

	// Override functions by implementation class
	virtual bool vInit(void) { return true; }
	virtual void vPostInit(void) { }
	virtual bool vUpdate(int deltaMs) { return false; }
	virtual void vOnChanged(void) { }
	virtual void vDraw(void) { }

	// for the editor
	//virtual TiXmlElement *VGenerateXml(void) = 0;

	// Override functions by interface class.
	virtual ComponentId VGetId(void) const { return GetIdFromName(VGetName()); }
	virtual const char *VGetName() const = 0;
	static ComponentId GetIdFromName(const char *componentStr)
	{
		void *rawId = HashedString::hash_name(componentStr);
		return reinterpret_cast<ComponentId>(rawId);
	}

private:
	void SetOwner(StrongActorPtr pOwner) { m_pOwner = pOwner; }
};