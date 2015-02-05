#include "Transform2dComponent.h"
#include "Math.h"
#include "String.h"

const char *Transform2dComponent::g_Name = "Transform2dComponent";

bool Transform2dComponent::VInit(TiXmlElement *pData)
{
	// Xml setup

	return true;
}

TiXmlElement *Transform2dComponent::VGenerateXml()
{
	return NULL;
}