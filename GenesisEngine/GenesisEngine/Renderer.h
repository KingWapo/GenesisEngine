#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>

#include "GLSLProgram.h"
#include "GLTexture.h"
#include "SpriteBatch.h"


class Renderer
{
private:
	SpriteBatch m_spriteBatch;
	std::string m_filePath;
	float m_startX;
	float m_startY;
	float m_width;
	float m_height;

public:
	Renderer();

	void Init();
};