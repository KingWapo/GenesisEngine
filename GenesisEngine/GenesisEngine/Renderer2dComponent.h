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
	Vector2 m_location;
	Vector2 m_spriteSize;
	std::string m_spriteLocation;
	SpriteBatch m_spriteBatch;

public:
	Renderer2dComponent() { m_location = Vector2(0, 0); m_spriteSize = Vector2(0, 0); m_spriteLocation = ""; }
	Renderer2dComponent(Vector2 pLocation, Vector2 pSpriteSize, std::string pSpriteLocation) { m_location = pLocation; m_spriteSize = pSpriteSize; m_spriteLocation = pSpriteLocation; }

	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	virtual bool vInit(void) override;
	//virtual TiXmlElement *VGenerateXml(void) override;

	virtual void VUpdate(int deltaMs);

};

