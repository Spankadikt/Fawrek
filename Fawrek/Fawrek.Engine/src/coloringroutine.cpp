#include "coloringroutine.h"
#include "utils.h"

ColoringRoutine::ColoringRoutine(const std::string& _sVertexShaderFilename,const std::string& _sFragmentShaderFilename)
{
	m_sVertexShaderFilename = _sVertexShaderFilename;
    m_sFragmentShaderFilename = _sFragmentShaderFilename;
}

ColoringRoutine::~ColoringRoutine()
{
}

int ColoringRoutine::Init()
{
	int shaderInit = Shader::Init();
    if (shaderInit != 0)
        return shaderInit;

    if (!AddShader(GL_VERTEX_SHADER, m_sVertexShaderFilename.c_str()))
        return 21;

    if (!AddShader(GL_FRAGMENT_SHADER, m_sFragmentShaderFilename.c_str()))
        return 22;

    if (!Finalize())
        return 23;

    m_wvpLocation = GetUniformLocation("gWVP");

    if (m_wvpLocation == 0xFFFFFFFF) {
        return 24;
    }

    return 0;
}

void ColoringRoutine::SetWVP(Matrix _WVP)
{
	glUniformMatrix4fv(m_wvpLocation, 1, GL_FALSE,&_WVP.m_m[0]);    
}