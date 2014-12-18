#include "iostream"
#include "texture.h"

Texture::Texture(const char *_filename,GLenum _textureTarget)
{
	filename = _filename;
	textureTarget = _textureTarget;
}

bool Texture::LoadTexture()
{
	/* load an image file directly as a new OpenGL texture */
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == texture )
	{
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
		return false;
	}

	return true;
}

void Texture::Bind(GLenum _textureUnit)
{
	glActiveTexture(_textureUnit);
	// select our current texture
    glBindTexture(textureTarget, texture );
}