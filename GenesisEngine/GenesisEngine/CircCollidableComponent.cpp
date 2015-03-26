#include "CircCollidableComponent.h"

const char *CircCollidableComponent::g_Name = "CircCollidableComponent";

CircCollidableComponent::CircCollidableComponent()
{
	m_offset = Vector2(0, 0);
	m_radius = 0;
}

CircCollidableComponent::CircCollidableComponent(float p_r)
{
	m_offset = Vector2(0, 0);
	m_radius = p_r;
}

CircCollidableComponent::CircCollidableComponent(Vector2 p_offset, float p_r)
{
	m_offset = p_offset;
	m_radius = p_r;
}


CircCollidableComponent::~CircCollidableComponent()
{
}

bool CircCollidableComponent::vUpdate(int deltaMs)
{

	return false;
}

void CircCollidableComponent::vOnChanged()
{

}

Circ2D CircCollidableComponent::getCirc()
{
	Circ2D tempCirc(0, 0, 0);
	if (m_transformation.get() != NULL)
	{
		tempCirc.setCirc(m_transformation.get()->GetTranslation().x,
			m_transformation.get()->GetTranslation().y, m_radius);
	}
	return tempCirc;
}
