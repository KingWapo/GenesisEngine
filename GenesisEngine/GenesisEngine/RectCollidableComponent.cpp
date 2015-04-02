#include "RectCollidableComponent.h"

RectCollidableComponent::RectCollidableComponent()
{
	m_rect = Rect2D();
	colType = ColliderType::Rect;
}

RectCollidableComponent::RectCollidableComponent(Rect2D p_rect, bool p_static)
{
	m_rect = p_rect;
	m_isStatic = p_static;
	colType = ColliderType::Rect;
}

bool RectCollidableComponent::vUpdate(int deltaMs)
{
	return false;
}

void RectCollidableComponent::vOnChanged()
{

}