//-----------------------------------------------------------------
// Renderable component meant to be inherited depending on the 
// renderer to be used (i.e. OpenGl, SDL, DirectX, etc.
//-----------------------------------------------------------------

#pragma once
#include "ActorComponent.h"

class RenderableComponent : public ActorComponent
{
protected:
	Vector2 m_location;
	Vector2 m_size;
	Vector2 m_cell;
	const char* m_spriteLocation;

private:
	bool m_drawable;

public:
	RenderableComponent();
	RenderableComponent(const char* p_fileLocation, Vector2 p_location, Vector2 p_size, Vector2 p_cell);

	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	virtual bool vInit(void) override;
	virtual void vPostInit(void) override;
	virtual void vUpdate(int deltaMs) override;
	virtual void vOnChanged(void) override;

	virtual void vDraw(void);

	void setDrawable(bool p_drawable) { m_drawable = p_drawable; }
	bool isDrawable() { return m_drawable; }

	void setDrawInformation(const char* p_fileLocation, Vector2 p_location, Vector2 p_size, Vector2 p_cell);
};

