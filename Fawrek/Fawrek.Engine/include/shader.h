#include "api.h"

#ifndef SHADER_H
#define	SHADER_H

#include "list"
#include "GL/glew.h"
#include "vector3.h"

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

class FAWREK_API Shader
{
public:

    Shader();

    virtual ~Shader();
    virtual int Init();

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
