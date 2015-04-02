#include "CircCollidableComponent.h"

CircCollidableComponent::CircCollidableComponent()
{
	m_circ = Circ2D();
	colType = ColliderType::Circ;
}

CircCollidableComponent::CircCollidableComponent(float p_r)
{
	m_circ.setRadius(p_r);
	colType = ColliderType::Circ;
}

CircCollidableComponent::CircCollidableComponent(Circ2D p_circ, bool p_static)
{
	m_circ = p_circ;
	m_isStatic = p_static;
}

bool CircCollidableComponent::vUpdate(int deltaMs)
{
	return false;
}

void CircCollidableComponent::vOnChanged()
{

}
