#include "stdio.h"
#include "string.h"

#include "utils.h"
#include "shader.h"

Shader::Shader()
{
    shaderProg = 0;
}


Shader::~Shader()
{
    // Delete the intermediate shader objects that have been added to the program
    // The list will only contain something if shaders were compiled but the object itself
    // was destroyed prior to linking.
    for (ShaderObjList::iterator it = shaderObjList.begin() ; it != shaderObjList.end() ; it++)
    {
        glDeleteShader(*it);
    }

    if (shaderProg != 0)
    {
        glDeleteProgram(shaderProg);
        shaderProg = 0;
    }
}


bool Shader::Init()
{
    shaderProg = glCreateProgram();

    if (shaderProg == 0) {
        fprintf(stderr, "Error creating shader program\n");
        return false;
    }

    return true;
}

// Use this method to add shaders to the program. When finished - call finalize()
bool Shader::AddShader(GLenum ShaderType, const char* pFilename)
{
    string s;
    
    if (!ReadFile(pFilename, s)) {
        return false;
    }
    
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        return false;
    }

    // Save the shader object - will be deleted in the destructor
    shaderObjList.push_back(ShaderObj);

    const GLchar* p[1];
    p[0] = s.c_str();
    GLint Lengths[1] = { (GLint)s.size() };

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling '%s': '%s'\n", pFilename, InfoLog);
        return false;
    }

    glAttachShader(shaderProg, ShaderObj);

    return true;
}


// After all the shaders have been added to the program call this function
// to link and validate the program.
bool Shader::Finalize()
{
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(shaderProg);

    glGetProgramiv(shaderProg, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        return false;
	}

    glValidateProgram(shaderProg);
    glGetProgramiv(shaderProg, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
     //   return false;
    }

    // Delete the intermediate shader objects that have been added to the program
    for (ShaderObjList::iterator it = shaderObjList.begin() ; it != shaderObjList.end() ; it++) {
        glDeleteShader(*it);
    }

    shaderObjList.clear();

    return GLCheckError();
}


void Shader::Enable()
{
    glUseProgram(shaderProg);
}


GLint Shader::GetUniformLocation(const char *_pUniformName)
{
    GLuint Location = glGetUniformLocation(shaderProg, _pUniformName);

    if (Location == 0xffffffff) {
        fprintf(stderr, "Warning! Unable to get the location of uniform '%s'\n", _pUniformName);
    }

    return Location;
}

GLint Shader::GetProgramParam(GLint _param)
{
    GLint ret;
    glGetProgramiv(shaderProg, _param, &ret);
    return ret;
}
