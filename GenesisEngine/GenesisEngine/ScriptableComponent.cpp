#include "ScriptableComponent.h"

const char *ScriptableComponent::g_Name = "ScriptableComponent";

ScriptableComponent::ScriptableComponent()
{
	m_name = NULL;
	m_pDomain = mono_jit_init("script.exe");
	m_pAssembly = mono_domain_assembly_open(m_pDomain, "script.exe");
}

ScriptableComponent::ScriptableComponent(const char* p_name)
{
	m_name = p_name;
}

ScriptableComponent::~ScriptableComponent()
{
}

bool ScriptableComponent::vInit()
{
	return true;
}

bool ScriptableComponent::vUpdate(int deltaMs)
{
	return true;
}

void ScriptableComponent::vOnChanged()
{

}