#include "api.h"

#ifndef SKINNINGROUTINE_H
#define	SKINNINGROUTINE_H

#include "shader.h"
#include "vector3.h"
#include "matrix.h"

class FAWREK_API SkinningRoutine : public Shader
{
public:

	static const uint MAX_BONES = 100;

    SkinningRoutine(const std::string& _sVertexShaderFilename,const std::string& _sFragmentShaderFilename);
    ~SkinningRoutine();

    virtual int Init();

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


#endif	//SKINNINGROUTINE_H