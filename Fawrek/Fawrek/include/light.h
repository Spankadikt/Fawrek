#ifndef LIGHT_H
#define	LIGHT_H

#include "shader.h"
#include "vector3.h"
#include "matrix.h"

struct DirectionalLight
{
    Vector3 Color;
    float AmbientIntensity;
	Vector3 Direction;
    float DiffuseIntensity;
};

class Light : public Shader
{
public:

    Light();

    virtual bool Init();

    void SetWVP(Matrix _WVP);
	void SetWorldMatrix(Matrix _W);
    void SetTextureUnit(unsigned int _textureUnit);
    void SetDirectionalLight(const DirectionalLight _light);
	void SetEyeWorldPos(const Vector3 _eyeWorldPos);
    void SetMatSpecularIntensity(float _intensity);
    void SetMatSpecularPower(float _power);

private:

    GLuint WVPLocation;
	GLuint worldMatrixLocation;
    GLuint samplerLocation;
	GLuint eyeWorldPosLocation;
    GLuint matSpecularIntensityLocation;
    GLuint matSpecularPowerLocation;

	struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint Direction;
        GLuint DiffuseIntensity;
    } dirLightLocation;
};


#endif	//LIGHT_H