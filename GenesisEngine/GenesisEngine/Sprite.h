#include "Vector2.h"

#include <GL/glew.h>
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>
#include <string>

// do glBufferData(...) on an std::vector<...>
template<class T>
inline void bufferData(GLenum target, const std::vector<T> &v, GLenum usage)
{
	glBufferData(target, v.size() * sizeof(T), &v[0], usage);
}

// get pointer offset of 'field' in struct 'type'
#define poffsetof(type, field) \
	((void *) (&((type *) 0)->field))

struct Sprite
{
	Vector2 m_position;		// world position to draw at.
	Vector2 m_cell;			// u, v offset in atlas
	Vector2 m_size;			// u, v rectangle size in atlas
	Vector2 m_velocity;		// it moves!


	void LoadTexture(std::string p_SpriteLocation)
	{
		
	}

	static void bindAttributes(GLuint p_position, GLuint p_cell, GLuint p_size, GLuint divisor = 1)
	{
		glVertexAttribPointer(p_position, 2, GL_FLOAT, GL_FALSE,
			sizeof(Sprite), poffsetof(Sprite, m_position));
		glEnableVertexAttribArray(p_position);
		glVertexAttribDivisor(p_position, divisor);

		glVertexAttribPointer(p_cell, 2, GL_FLOAT, GL_FALSE,
			sizeof(Sprite), poffsetof(Sprite, m_cell));
		glEnableVertexAttribArray(p_cell);
		glVertexAttribDivisor(p_cell, divisor);

		glVertexAttribPointer(p_size, 2, GL_FLOAT, GL_FALSE,
			sizeof(Sprite), poffsetof(Sprite, m_size));
		glEnableVertexAttribArray(p_size);
		glVertexAttribDivisor(p_size, divisor);
	}
};