#include "api.h"

#ifndef LIGHT_H
#define	LIGHT_H

#include "shader.h"
#include "vector3.h"
#include "matrix.h"

struct FAWREK_API BaseLight
{
    Vector3 m_color;
    float m_fAmbientIntensity;
    float m_fDiffuseIntensity;

    BaseLight()
    {
        m_color = Vector3(0.0f, 0.0f, 0.0f);
        m_fAmbientIntensity = 0.0f;
        m_fDiffuseIntensity = 0.0f;
    }

};

struct FAWREK_API DirectionalLight : public BaseLight
{        
    Vector3 m_direction;

    DirectionalLight()
    {
        m_direction = Vector3(0.0f, 0.0f, 0.0f);
    }
};

class FAWREK_API Light : public Shader
{
public:

	static const uint MAX_BONES = 100;

    Light(const std::string& _sVertexShaderFilename,const std::string& _sFragmentShaderFilename);
    ~Light();

    virtual bool Init();

    void SetWVP(Matrix _WVP);
	void SetWorldMatrix(Matrix _W);
    void SetTextureUnit(unsigned int _uiTextureUnit);
    void SetDirectionalLight(const DirectionalLight _light);
	void SetEyeWorldPos(const Vector3 _eyeWorldPos);
    void SetMatSpecularIntensity(float _fIntensity);
    void SetMatSpecularPower(float _fPower);
	void SetBoneTransform(uint _uiIndex, const Matrix _transform);

private:
    string m_sVertexShaderFilename;
    string m_sFragmentShaderFilename;

    GLuint m_wvpLocation;
	GLuint m_worldMatrixLocation;
    GLuint m_samplerLocation;
	GLuint m_eyeWorldPosLocation;
    GLuint m_matSpecularIntensityLocation;
    GLuint m_matSpecularPowerLocation;

	struct {
        GLuint m_color;
        GLuint m_ambientIntensity;
        GLuint m_direction;
        GLuint m_diffuseIntensity;
    } m_dirLightLocation;

	GLuint m_boneLocation[MAX_BONES];
};


#endif	//LIGHT_H