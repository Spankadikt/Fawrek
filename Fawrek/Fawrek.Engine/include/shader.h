#include "api.h"

#ifndef SHADER_H
#define	SHADER_H

#include "list"
#include "GL/glew.h"
#include "directionallight.h"

/*struct FAWREK_API BaseLight
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
};*/

class FAWREK_API Shader
{
public:

    Shader();

    virtual ~Shader();
    virtual int Init();

	virtual void SetWVP(Matrix _WVP) = 0;
	virtual void SetWorldMatrix(Matrix _W) = 0;
    virtual void SetTextureUnit(unsigned int _uiTextureUnit) = 0;
    virtual void SetDirectionalLight(DirectionalLight* _light) = 0;
	virtual void SetEyeWorldPos(const Vector3 _eyeWorldPos) = 0;
    virtual void SetMatSpecularIntensity(float _fIntensity) = 0;
    virtual void SetMatSpecularPower(float _fPower) = 0;
	virtual void SetBoneTransform(uint _uiIndex, const Matrix _transform) = 0;

    void Enable();

protected:

    bool AddShader(GLenum ShaderType, const char* _pFilename);
    bool Finalize();

    GLint GetUniformLocation(const char* _pUniformName);   
    GLint GetProgramParam(GLint _param);  
    GLuint m_shaderProg;


    
private:

    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;
};

#endif	//SHADER
