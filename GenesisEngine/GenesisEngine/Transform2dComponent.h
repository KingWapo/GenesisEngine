#pragma once

#include "ActorComponent.h"
#include "Transformation2d.h"

class Transform2dComponent : public ActorComponent
{
private:
	Transformation2d m_transform;
public:
	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	Transform2dComponent(void) { m_transform = Transformation2d(); }
	virtual bool vInit() override;
	//virtual TiXmlElement *VGenerateXml(void) override;

	// Transform functions
	Transformation2d GetTransform(void) const { return m_transform; }
	void SetTransform(const Transformation2d newTransform) { m_transform = newTransform; }
	Vector2 GetTranslation(void) const { return m_transform.getTranslation(); }
	void SetTranslation(const Vector2 newTranslation) { m_transform.setTranslation(newTranslation); }
	float GetRotation(void) const { return m_transform.GetRotation(); }
	void SetRotation(const float newRotation) { m_transform.SetRotation(newRotation); }

	void move(float deltaH, float deltaV);
};