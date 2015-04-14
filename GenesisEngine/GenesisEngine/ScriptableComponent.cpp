#include "ScriptableComponent.h"

const char *ScriptableComponent::g_Name = "ScriptableComponent";

ScriptableComponent::ScriptableComponent()
{
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