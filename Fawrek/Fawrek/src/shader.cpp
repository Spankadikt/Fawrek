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
bool Shader::AddShader(GLenum _shaderType, const char *_pFilename)
{
    string s;
    
    if (!ReadFile(_pFilename, s)) {
        return false;
    }
    
    GLuint shaderObj = glCreateShader(_shaderType);

    if (shaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", _shaderType);
        return false;
    }

    // Save the shader object - will be deleted in the destructor
    shaderObjList.push_back(shaderObj);

    const GLchar* p[1];
    p[0] = s.c_str();
    GLint lengths[1] = { (GLint)s.size() };

    glShaderSource(shaderObj, 1, p, lengths);

    glCompileShader(shaderObj);

    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling '%s': '%s'\n", _pFilename, InfoLog);
        return false;
    }

    glAttachShader(shaderProg, shaderObj);

    return true;
}


// After all the shaders have been added to the program call this function
// to link and validate the program.
bool Shader::Finalize()
{
    GLint success = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(shaderProg);

    glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
	if (success == 0) {
		glGetProgramInfoLog(shaderProg, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
        return false;
	}

    glValidateProgram(shaderProg);
    glGetProgramiv(shaderProg, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProg, sizeof(errorLog), NULL, errorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", errorLog);
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
