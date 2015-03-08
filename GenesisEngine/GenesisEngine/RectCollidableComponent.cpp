#include "RectCollidableComponent.h"

RectCollidableComponent::RectCollidableComponent()
{
	m_offset = Vector2(0, 0);
	width = 0.0f;
	height = 0.0f;
}

RectCollidableComponent::RectCollidableComponent(float p_width, float p_height)
{
	m_offset = Vector2(0, 0);
	width = p_width;
	height = p_height;
}

RectCollidableComponent::RectCollidableComponent(Vector2 p_offset, float p_width, float p_height)
{
	m_offset = p_offset;
	width = p_width;
	height = p_height;
}

bool RectCollidableComponent::vUpdate(int deltaMs)
{

	return false;
}

void RectCollidableComponent::vOnChanged()
{

}

/*bool RectCollidableComponent::isColliding(RectCollidableComponent other) {
	return ((m_transformation->get()))
}*/

Rect2D RectCollidableComponent::getRect()
{
	Rect2D tempRect(0, 0, 0, 0);
	if (m_transformation.get() != NULL)
	{
		tempRect.setRect(m_transformation->GetTranslation().x + m_offset.x,
			m_transformation->GetTranslation().y + m_offset.y,
			width, height);
	}
	return tempRect;
}

Vector2 RectCollidableComponent::getSize()
{
	return Vector2(width, height);
}

Vector2 RectCollidableComponent::getOffset()
{
	return m_offset;
}

void RectCollidableComponent::setWidth(float p_w)
{
	width = p_w;
}

void RectCollidableComponent::setHeight(float p_h)
{
	height = p_h;
}

void RectCollidableComponent::setSize(float p_w, float p_h)
{
	width = p_w;
	height = p_h;
}

void RectCollidableComponent::setOffset(Vector2 p_offset)
{
	m_offset = p_offset;
}