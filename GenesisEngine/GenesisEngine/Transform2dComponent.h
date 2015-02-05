#include "ActorComponent.h"
#include "Transformation.h"

class Transform2dComponent : public ActorComponent
{
	Transformation2d m_transform;
public:
	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	Transform2dComponent(void) { m_transform = Transformation2d(); }
	virtual bool VInit(TiXmlElement *pData) override;
	virtual TiXmlElement *VGenerateXml(void) override;

	// Transform functions
	Transformation2d GetTransform(void) const { return m_transform; }
	void SetTransform(const Transformation2d newTransform) { m_transform = newTransform; }
	Vector2 GetLocation(void) const { return m_transform.GetLocation(); }
	void SetLocation(const Vector2 newLocation) { m_transform.SetLocation(newLocation); }
	float GetRotation(void) const { return m_transform.GetRotation(); }
	void SetRotation(const float newRotation) { m_transform.SetRotation(newRotation); }
};