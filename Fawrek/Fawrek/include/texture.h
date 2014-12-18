#ifndef TEXTURE_H
#define TEXTURE_H

#include "glew.h"
#include "stdio.h"
#include "windows.h"
#include "SOIL.h"

class Texture
{
public:
	Texture(const char *_filename,GLenum _textureTarget);

	bool LoadTexture();
	void Bind(GLenum _textureUnit);

private:
	GLuint texture;
	const char *filename;
	GLenum textureTarget;
};

#endif //TEXTURE_H