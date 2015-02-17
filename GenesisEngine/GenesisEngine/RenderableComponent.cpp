#include "RenderableComponent.h"

const char *RenderableComponent::g_Name = "RenderableComponent";

RenderableComponent::RenderableComponent()
{
	m_spriteLocation = "";
	m_location = Vector2(0,0);
	m_size = Vector2(0,0);
	m_cell = Vector2(0,0);
}

RenderableComponent::RenderableComponent(const char* p_fileLocation, Vector2 p_location, Vector2 p_size, Vector2 p_cell)
{
	m_spriteLocation = p_fileLocation;
	m_location = p_location;
	m_size = p_size;
	m_cell = p_cell;
}

bool RenderableComponent::vInit()
{
	return true;
}

void RenderableComponent::vPostInit()
{

}

void RenderableComponent::vUpdate(int deltaMs)
{

}

void RenderableComponent::vOnChanged()
{

}

void RenderableComponent::vDraw()
{

}

void RenderableComponent::setDrawInformation(const char* p_fileLocation, Vector2 p_location, Vector2 p_size, Vector2 p_cell)
{
	m_spriteLocation = p_fileLocation;
	m_location = p_location;
	m_size = p_size;
	m_cell = p_cell;
}