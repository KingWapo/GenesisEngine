#include "CircCollidableComponent.h"


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

bool CircCollidableComponent::vInit()
{
	if (m_pOwner != nullptr)
	{
		Actor* l_owner = static_cast<Actor*>(m_pOwner.get());
		p_transformation = l_owner->GetComponent<Transform2dComponent>("Transform2dComponent");
		if (p_transformation.get() != NULL)
		{
			return true;
		}
	}
	return false;
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
	if (p_transformation.get() != NULL)
	{
		tempCirc.setCirc(p_transformation.get()->GetLocation().x,
			p_transformation.get()->GetLocation().y, m_radius);
	}
	return tempCirc;
}
