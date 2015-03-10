#include "RectCollidableComponent.h"
#include "PhysicsComponent.h"

const char *RectCollidableComponent::g_Name = "RectCollidableComponent";

RectCollidableComponent::RectCollidableComponent()
{
	m_offset = Vector2(0, 0);
	width = 0.0f;
	height = 0.0f;
}

RectCollidableComponent::RectCollidableComponent(float p_width, float p_height, bool p_static)
{
	m_offset = Vector2(0, 0);
	width = p_width;
	height = p_height;
	isStatic = p_static;
}

RectCollidableComponent::RectCollidableComponent(Vector2 p_offset, float p_width, float p_height, bool p_static)
{
	m_offset = p_offset;
	width = p_width;
	height = p_height;
	isStatic = p_static;
}

bool RectCollidableComponent::vUpdate(int deltaMs)
{

	return false;
}

void RectCollidableComponent::vOnChanged()
{

}

bool RectCollidableComponent::isColliding(RectCollidableComponent &other) {
	float thisX = m_transformation->GetTranslation().x;
	float thisY = m_transformation->GetTranslation().y;

	float otherX = other.m_transformation->GetTranslation().x;
	float otherY = other.m_transformation->GetTranslation().y;

	bool insideX = (thisX < otherX + other.width && thisX > otherX) ||
		(thisX + width > otherX && thisX < otherX);

	bool insideY = (thisY < otherY + other.height && thisY > otherY) ||
		(thisY + height > otherY && thisY < otherY);

	return insideX && insideY;
}

void RectCollidableComponent::resolveCollision(RectCollidableComponent &other) {
	Vector2 dist = m_transformation->GetTranslation() - other.m_transformation->GetTranslation();

	if (!isStatic) {
		Vector2 newPos = m_transformation->GetTranslation();

		if (abs(dist.x) > abs(dist.y)) {
			if (dist.x < 0) {
				newPos.x += (abs(dist.x) - width);
			}
			else {
				newPos.x -= (abs(dist.x) - other.width);
			}

			StrongActorPtr l_ownerPtr = m_pOwner.lock();
			Actor* l_owner = static_cast<Actor*>(l_ownerPtr.get());
			shared_ptr<PhysicsComponent> physics = l_owner->GetComponent<PhysicsComponent>("PhysicsComponent");

			if (physics != NULL) {
				physics->setVelocity(Vector2(0.0f, physics->getVelocity().y));
			}
		} else {
			if (dist.y < 0) {
				newPos.y += (abs(dist.y) - height);
			}
			else {
				newPos.y -= (abs(dist.y) - other.height);
			}

			StrongActorPtr l_ownerPtr = m_pOwner.lock();
			Actor* l_owner = static_cast<Actor*>(l_ownerPtr.get());
			shared_ptr<PhysicsComponent> physics = l_owner->GetComponent<PhysicsComponent>("PhysicsComponent");
			if (physics != NULL) {
				physics->setVelocity(Vector2(physics->getVelocity().x, 0.0f));
			}
		}

		m_transformation->SetTranslation(newPos);
	}
}

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

Transform2dComponent RectCollidableComponent::getTransform() {
	return *m_transformation.get();
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