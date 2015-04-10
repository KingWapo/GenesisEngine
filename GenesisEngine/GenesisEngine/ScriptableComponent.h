#pragma once
#include "ActorComponent.h"

class ScriptableComponent :
	public ActorComponent
{
public:
	ScriptableComponent();
	~ScriptableComponent();

	static const char* g_Name;

	// Override functions
	virtual bool vInit(void);
	virtual bool vUpdate(int deltaMs);
	virtual void vOnChanged(void);
	virtual const char* VGetName() const { return g_Name; }
};

