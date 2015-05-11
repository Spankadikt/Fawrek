#include "api.h"

#ifndef LIGHTINGROUTINE_H
#define	LIGHTINGROUTINE_H

#include "shader.h"

class FAWREK_API LightingRoutine : public Shader
{
public:

	static const uint MAX_BONES = 100;

    LightingRoutine(const std::string& _sVertexShaderFilename,const std::string& _sFragmentShaderFilename);
    ~LightingRoutine();

    virtual int Init();

    virtual void SetWVP(Matrix _WVP);
	virtual void SetWorldMatrix(Matrix _W);
    virtual void SetTextureUnit(unsigned int _uiTextureUnit);
    virtual void SetDirectionalLight(DirectionalLight* _light);
	virtual void SetEyeWorldPos(const Vector3 _eyeWorldPos);
    virtual void SetMatSpecularIntensity(float _fIntensity);
    virtual void SetMatSpecularPower(float _fPower);
	virtual void SetBoneTransform(uint _uiIndex, const Matrix _transform);

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


#endif	//LIGHTINGROUTINE_H