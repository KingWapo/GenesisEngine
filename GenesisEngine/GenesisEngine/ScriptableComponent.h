#pragma once
#include "ActorComponent.h"
#include <mono\metadata\appdomain.h>
#include <mono\metadata\assembly.h>
#include <mono\jit\jit.h>

class ScriptableComponent :
	public ActorComponent
{
public:
	ScriptableComponent();
	ScriptableComponent(const char* p_name);
	~ScriptableComponent();

	static const char* g_Name;

	// Override functions
	virtual bool vInit(void);
	virtual bool vUpdate(int deltaMs);
	virtual void vOnChanged(void);
	virtual const char* VGetName() const { return g_Name; }

private:
	const char *m_name;

	// Mono Variables
	MonoDomain *m_pDomain;
	MonoAssembly *m_pAssembly;
	MonoImage *m_pImage;
};

