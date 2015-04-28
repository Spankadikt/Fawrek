#include "api.h"

#ifndef SHADER_H
#define	SHADER_H

#include "list"
#include "GL/glew.h"

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
