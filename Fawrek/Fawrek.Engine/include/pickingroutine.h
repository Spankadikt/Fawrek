#include "api.h"

#ifndef PICKINGROUTINE_H
#define	PICKINGROUTINE_H

#include "shader.h"
#include "matrix.h"

class PickingRoutine : public Shader
{
public:

    PickingRoutine(const std::string& _sVertexShaderFilename,const std::string& _sFragmentShaderFilename);
	~PickingRoutine();

    virtual int Init();

    virtual void SetWVP(Matrix _WVP);
	virtual void SetWorldMatrix(Matrix _W){};
    virtual void SetTextureUnit(unsigned int _uiTextureUnit){};
    virtual void SetDirectionalLight(DirectionalLight* _light){};
	virtual void SetEyeWorldPos(const Vector3 _eyeWorldPos){};
    virtual void SetMatSpecularIntensity(float _fIntensity){};
    virtual void SetMatSpecularPower(float _fPower){};
	virtual void SetBoneTransform(uint _uiIndex, const Matrix _transform){};

    void SetObjectIndex(int _nObjectIndex);  
    void SetDrawIndex(int _nDrawIndex);
    
private:
    string m_sVertexShaderFilename;
    string m_sFragmentShaderFilename;

    GLuint m_wvpLocation;
    GLuint m_drawIndexLocation;
    GLuint m_objectIndexLocation;
};

#endif//PICKINGROUTINE_H