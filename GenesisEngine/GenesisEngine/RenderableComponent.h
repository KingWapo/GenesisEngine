//-----------------------------------------------------------------
// Renderable component meant to be inherited depending on the 
// renderer to be used (i.e. OpenGl, SDL, DirectX, etc.)
//-----------------------------------------------------------------

#pragma once
#include "ActorComponent.h"
#include "Point2D.h"

class RenderableComponent : public ActorComponent
{
protected:
	Point2DF m_location;
	Point2DF m_size;
	Point2DF m_cell;
	const char* m_spriteFileLocation;

private:
	bool m_drawable;
	static const char *g_Name;

public:
	RenderableComponent();
	RenderableComponent(const char* p_fileLocation, Point2DF p_location, Point2DF p_size, Point2DF p_cell);

	void setDrawInformation(const char* p_fileLocation, Point2DF p_location, Point2DF p_size, Point2DF p_cell);

	virtual void vDraw(void) = 0;

	void setDrawable(bool p_drawable) { m_drawable = p_drawable; }
	bool isDrawable() const { return m_drawable; }

	virtual const char *VGetName() const { return g_Name; }
};

