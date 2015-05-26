#include "api.h"

#ifndef COLORINGROUTINE_H
#define	COLORINGROUTINE_H

#include "shader.h"

class FAWREK_API ColoringRoutine : public Shader
{
public:
    ColoringRoutine(const std::string& _sVertexShaderFilename,const std::string& _sFragmentShaderFilename);
    ~ColoringRoutine();

    virtual int Init();

    virtual void SetWVP(Matrix _WVP);
	virtual void SetWorldMatrix(Matrix _W){};
    virtual void SetTextureUnit(unsigned int _uiTextureUnit){};
    virtual void SetDirectionalLight(DirectionalLight* _light){};
	virtual void SetEyeWorldPos(const Vector3 _eyeWorldPos){};
    virtual void SetMatSpecularIntensity(float _fIntensity){};
    virtual void SetMatSpecularPower(float _fPower){};
	virtual void SetBoneTransform(uint _uiIndex, const Matrix _transform){};

private:
    string m_sVertexShaderFilename;
    string m_sFragmentShaderFilename;

    GLuint m_wvpLocation;
};


#endif	//LIGHTINGROUTINE_H