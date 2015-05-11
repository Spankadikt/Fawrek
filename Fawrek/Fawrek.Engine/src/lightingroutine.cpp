#include "assert.h"

#include "lightingroutine.h"
#include "utils.h"

LightingRoutine::LightingRoutine(const std::string& _sVertexShaderFilename,const std::string& _sFragmentShaderFilename)
{
    m_sVertexShaderFilename = _sVertexShaderFilename;
    m_sFragmentShaderFilename = _sFragmentShaderFilename;
}

LightingRoutine::~LightingRoutine()
{
}


int LightingRoutine::Init()
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
	m_worldMatrixLocation = GetUniformLocation("gWorld");
    m_samplerLocation = GetUniformLocation("gSampler");
    m_dirLightLocation.m_color = GetUniformLocation("gDirectionalLight.Color");
    m_dirLightLocation.m_ambientIntensity = GetUniformLocation("gDirectionalLight.AmbientIntensity");
	m_dirLightLocation.m_direction = GetUniformLocation("gDirectionalLight.Direction");
    m_dirLightLocation.m_diffuseIntensity = GetUniformLocation("gDirectionalLight.DiffuseIntensity");
	m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
    m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");

    if (m_dirLightLocation.m_ambientIntensity == 0xFFFFFFFF ||
        m_wvpLocation == 0xFFFFFFFF ||
        m_worldMatrixLocation == 0xFFFFFFFF ||
        m_samplerLocation == 0xFFFFFFFF ||
        m_dirLightLocation.m_color == 0xFFFFFFFF ||
        m_dirLightLocation.m_diffuseIntensity == 0xFFFFFFFF ||
        m_dirLightLocation.m_direction == 0xFFFFFFFF ||
		m_matSpecularIntensityLocation == 0xFFFFFFFF ||
        m_matSpecularPowerLocation == 0xFFFFFFFF)
	{
        return 24;
    }

	for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_boneLocation) ; i++) {
        char name[128];
        memset(name, 0, sizeof(name));
        SNPRINTF(name, sizeof(name), "gBones[%d]", i);
        m_boneLocation[i] = GetUniformLocation(name);
    }

    return 0;
}

void LightingRoutine::SetWVP(Matrix _WVP)
{
	glUniformMatrix4fv(m_wvpLocation, 1, GL_FALSE,&_WVP.m_m[0]);    
}

void LightingRoutine::SetWorldMatrix(Matrix _worldInverse)
{
	glUniformMatrix4fv(m_worldMatrixLocation, 1, GL_FALSE, &_worldInverse.m_m[0]);
}


void LightingRoutine::SetTextureUnit(unsigned int _textureUnit)
{
    glUniform1i(m_samplerLocation, _textureUnit);
}


void LightingRoutine::SetDirectionalLight(DirectionalLight* _light)
{
    glUniform3f(m_dirLightLocation.m_color, _light->m_color.m_fX, _light->m_color.m_fY, _light->m_color.m_fZ);
    glUniform1f(m_dirLightLocation.m_ambientIntensity, _light->m_fAmbientIntensity);
    Vector3 direction = _light->m_direction;
    direction = direction.Normalize();
    glUniform3f(m_dirLightLocation.m_direction, direction.m_fX, direction.m_fY, direction.m_fZ);
    glUniform1f(m_dirLightLocation.m_diffuseIntensity, _light->m_fDiffuseIntensity);
}

void LightingRoutine::SetEyeWorldPos(const Vector3 _eyeWorldPos)
{
    glUniform3f(m_eyeWorldPosLocation, _eyeWorldPos.m_fX, _eyeWorldPos.m_fY, _eyeWorldPos.m_fZ);
}

void LightingRoutine::SetMatSpecularIntensity(float _intensity)
{
    glUniform1f(m_matSpecularIntensityLocation, _intensity);
}

void LightingRoutine::SetMatSpecularPower(float _power)
{
    glUniform1f(m_matSpecularPowerLocation, _power);
}

void LightingRoutine::SetBoneTransform(uint _index, const Matrix _transform)
{
    assert(_index < MAX_BONES);
	glUniformMatrix4fv(m_boneLocation[_index], 1, GL_FALSE, &_transform.m_m[0]);       
}