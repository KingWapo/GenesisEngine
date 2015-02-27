#include "RenderableComponent.h"

const char *RenderableComponent::g_Name = "RenderableComponent";

RenderableComponent::RenderableComponent()
{
	m_drawable = false;
	m_spriteFileLocation = "";
}

RenderableComponent::RenderableComponent(const char* p_fileLocation, Point2DF p_location, Point2DF p_size, Point2DF p_cell)
{
	m_drawable = false;

	m_spriteFileLocation = p_fileLocation;
	m_location = p_location;
	m_size = p_size;
	m_cell = p_cell;
}

void RenderableComponent::setDrawInformation(const char* p_fileLocation, Point2DF p_location, Point2DF p_size, Point2DF p_cell)
{
	m_spriteFileLocation = p_fileLocation;
	m_location = p_location;
	m_size = p_size;
	m_cell = p_cell;
}