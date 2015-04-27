#include "api.h"

#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include "stdio.h"
#include "windows.h"
#include "SOIL/SOIL.h"

class FAWREK_API Texture
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