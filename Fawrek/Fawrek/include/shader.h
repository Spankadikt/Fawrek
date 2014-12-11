#ifndef SHADER_H
#define	SHADER_H

#include "list"
#include "glew.h"

class Shader
{
public:

    Shader();

    virtual ~Shader();

    virtual bool Init();

    void Enable();

protected:

    bool AddShader(GLenum ShaderType, const char *_pFilename);

    bool Finalize();

    GLint GetUniformLocation(const char *_pUniformName);
    
    GLint GetProgramParam(GLint _param);
    
    GLuint shaderProg;    
    
private:

    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList shaderObjList;
};

#endif	//SHADER
