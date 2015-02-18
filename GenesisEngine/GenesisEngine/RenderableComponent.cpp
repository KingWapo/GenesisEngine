#include "RenderableComponent.h"

const char *RenderableComponent::g_Name = "RenderableComponent";

RenderableComponent::RenderableComponent()
{
	m_spriteFileLocation = "";
}

RenderableComponent::RenderableComponent(const char* p_fileLocation, Point2D p_location, Point2D p_size, Point2D p_cell)
{
	m_spriteFileLocation = p_fileLocation;
	m_location = p_location;
	m_size = p_size;
	m_cell = p_cell;
}

void RenderableComponent::setDrawInformation(const char* p_fileLocation, Point2D p_location, Point2D p_size, Point2D p_cell)
{
	m_spriteFileLocation = p_fileLocation;
	m_location = p_location;
	m_size = p_size;
	m_cell = p_cell;
}