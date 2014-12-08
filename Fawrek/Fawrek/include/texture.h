#ifndef TEXTURE_H
#define TEXTURE_H

#include "glew.h"
#include "stdio.h"
#include "windows.h"

class Texture
{
public:
	Texture(const char *_filename,GLenum _textureTarget, int _wrap);

	bool LoadTextureRAW();
	void Bind(GLenum _textureUnit);

private:
	GLuint texture;
    int width, height;
	const char *filename;
	GLenum textureTarget;
	int wrap;
};

#endif //TEXTURE_H