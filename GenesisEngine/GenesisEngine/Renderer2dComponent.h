#pragma once
#include "ActorComponent.h"

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>

#include "GLSLProgram.h"
#include "GLTexture.h"
#include "SpriteBatch.h"
#include "Renderer.h"

class Renderer2dComponent : public ActorComponent
{
	Vector2 location;
	Vector2 spriteSize;
	std::string spriteLocation;
	SpriteBatch spriteBatch;

public:
	Renderer2dComponent() { location = Vector2(0, 0); spriteSize = Vector2(0, 0); spriteLocation = ""; }
	Renderer2dComponent(Vector2 pLocation, Vector2 pSpriteSize, std::string pSpriteLocation) { location = pLocation; spriteSize = pSpriteSize; spriteLocation = pSpriteLocation; }

	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	virtual bool VInit(TiXmlElement *pData) override;
	virtual TiXmlElement *VGenerateXml(void) override;

	virtual void VUpdate(int deltaMs);

};

