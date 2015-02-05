#include "Renderer2dComponent.h"
#include "Errors.h"
#include "ResourceManager.h"

#include <iostream>
#include <string>

const char *Renderer2dComponent::g_Name = "Renderer2dComponent";

void Renderer2dComponent::VUpdate(int deltaMs) {
	spriteBatch.begin();

	glm::vec4 pos(location.x, location.y, spriteSize.x, spriteSize.y);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::getTexture(spriteLocation);
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	spriteBatch.draw(pos, uv, texture.id, 0.0f, color);

	spriteBatch.end();

	spriteBatch.renderBatch();
}

bool Renderer2dComponent::VInit(TiXmlElement *pData)
{
	return true;
}

TiXmlElement *Renderer2dComponent::VGenerateXml()
{
	return NULL;
}