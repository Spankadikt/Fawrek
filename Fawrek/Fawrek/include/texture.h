#ifndef TEXTURE_H
#define TEXTURE_H

#include "glew.h"
#include "stdio.h"
#include "windows.h"
#include "SOIL.h"

class Texture
{
public:
	Texture(const char* _pcFilename,GLenum _textureTarget);

	bool LoadTexture();
	void Bind(GLenum _textureUnit);

private:
	GLuint m_texture;
	const char* m_pcFilename;
	GLenum m_textureTarget;
};

#endif //TEXTURE_H