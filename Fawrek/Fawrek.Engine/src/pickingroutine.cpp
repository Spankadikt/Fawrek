#include "pickingroutine.h"
#include "utils.h"

PickingRoutine::PickingRoutine(const std::string& _sVertexShaderFilename,const std::string& _sFragmentShaderFilename)
{   
	m_sVertexShaderFilename = _sVertexShaderFilename;
    m_sFragmentShaderFilename = _sFragmentShaderFilename;
}

PickingRoutine::~PickingRoutine()
{
}

int PickingRoutine::Init()
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
    m_objectIndexLocation = GetUniformLocation("gObjectIndex");
    m_drawIndexLocation = GetUniformLocation("gDrawIndex");

    if (m_wvpLocation == 0xFFFFFFFF ||
        m_objectIndexLocation == 0xFFFFFFFF ||
        m_drawIndexLocation == 0xFFFFFFFF) {
        return 24;
    }

    return 0;
}


void PickingRoutine::SetWVP(Matrix _WVP)
{
    glUniformMatrix4fv(m_wvpLocation, 1, GL_FALSE, &_WVP.m_m[0]);    
}


void PickingRoutine::SetDrawIndex(int _nDrawIndex)
{
    glUniform1ui(m_drawIndexLocation, _nDrawIndex);
}


void PickingRoutine::SetObjectIndex(int _nObjectIndex)
{
    glUniform1ui(m_objectIndexLocation, _nObjectIndex);
}