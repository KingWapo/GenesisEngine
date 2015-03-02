#include "Transform2dComponent.h"
#include "Math.h"
#include "String.h"

const char *Transform2dComponent::g_Name = "Transform2dComponent";

bool Transform2dComponent::vInit()
{
	return true;
}

void Transform2dComponent::move(float deltaH, float deltaV) {
	Vector2 loc = m_transform.getTranslation();
	m_transform.setTranslation(Vector2(loc.x + deltaH, loc.y + deltaV));
}