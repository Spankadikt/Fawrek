#ifndef LIGHT_H
#define	LIGHT_H

#include "shader.h"
#include "vector3.h"
#include "matrix.h"

struct BaseLight
{
    Vector3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;

    BaseLight()
    {
        Color = Vector3(0.0f, 0.0f, 0.0f);
        AmbientIntensity = 0.0f;
        DiffuseIntensity = 0.0f;
    }

};

struct DirectionalLight : public BaseLight
{        
    Vector3 Direction;

    DirectionalLight()
    {
        Direction = Vector3(0.0f, 0.0f, 0.0f);
    }
};

class Light : public Shader
{
public:

	static const uint MAX_BONES = 100;

    Light();

    virtual bool Init();

    void SetWVP(Matrix _WVP);
	void SetWorldMatrix(Matrix _W);
    void SetTextureUnit(unsigned int _textureUnit);
    void SetDirectionalLight(const DirectionalLight _light);
	void SetEyeWorldPos(const Vector3 _eyeWorldPos);
    void SetMatSpecularIntensity(float _intensity);
    void SetMatSpecularPower(float _power);
	void SetBoneTransform(uint _index, const Matrix _transform);

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

	GLuint boneLocation[MAX_BONES];
};


#endif	//LIGHT_H