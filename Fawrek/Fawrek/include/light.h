#ifndef LIGHT_H
#define	LIGHT_H

#include "shader.h"
#include "vector3.h"
#include "matrix.h"

struct DirectionalLight
{
    Vector3 Color;
    float AmbientIntensity;
};

class Light : public Shader
{
public:

    Light();

    virtual bool Init();

    void SetWVP(Matrix _WVP);
    void SetTextureUnit(unsigned int _textureUnit);
    void SetDirectionalLight(const DirectionalLight &_light);

private:

    GLuint WVPLocation;
    GLuint samplerLocation;
    GLuint dirLightColorLocation;
    GLuint dirLightAmbientIntensityLocation;
};


#endif	//LIGHT_H