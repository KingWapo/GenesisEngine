#include "CircCollidableComponent.h"

ColliderType CircCollidableComponent::colType = ColliderType::Circ;

CircCollidableComponent::CircCollidableComponent()
{
	m_circ = Circ2D();
}

CircCollidableComponent::CircCollidableComponent(float p_r)
{
	m_circ.setRadius(p_r);
}

CircCollidableComponent::CircCollidableComponent(Circ2D p_circ, bool p_static)
{
	m_circ = p_circ;
	m_isStatic = p_static;
}

bool CircCollidableComponent::vUpdate(int deltaMs)
{
	m_circ.setLocation(m_transformation->GetTranslation());
	return false;
}

void CircCollidableComponent::vOnChanged()
{

}
