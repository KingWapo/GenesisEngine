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
	/* Prof. B: Vector2 has floating point precision but SDL_Rect has int precision
				This needs to be the same, at some level you should either be using floats or ints
				but not combining them.  I'm swapping it for my own point2d. */

	Point2D m_location;
	Point2D m_size;
	Point2D m_cell;
	const char* m_spriteFileLocation;

private:
	bool m_drawable;
	static const char *g_Name;

public:
	RenderableComponent();
	RenderableComponent(const char* p_fileLocation, Point2D p_location, Point2D p_size, Point2D p_cell);

	void setDrawInformation(const char* p_fileLocation, Point2D p_location, Point2D p_size, Point2D p_cell);

	// Prof. B: The members from ActorComponent are identical so just leave them out
	//			you only need to include them here IF you actually override them with something new.

	// Prof. B: This function cannot work in the parent, it requires specialization in the child to make
	//			sense.  So, let's make it PURE virtual (aka abstract) so the child MUST override it.
	virtual void vDraw(void) = 0;

	void setDrawable(bool p_drawable) { m_drawable = p_drawable; }
	bool isDrawable() const { return m_drawable; }

	virtual const char *VGetName() const { return g_Name; }
};

