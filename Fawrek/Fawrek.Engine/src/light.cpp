#include "assert.h"

#include "light.h"
#include "utils.h"

Light::Light(const std::string& _sVertexShaderFilename,const std::string& _sFragmentShaderFilename)
{
    m_sVertexShaderFilename = _sVertexShaderFilename;
    m_sFragmentShaderFilename = _sFragmentShaderFilename;
}

Light::~Light()
{
}


bool Light::Init()
{
    if (!Shader::Init())
        return false;

    if (!AddShader(GL_VERTEX_SHADER, m_sVertexShaderFilename.c_str()))
        return false;

    if (!AddShader(GL_FRAGMENT_SHADER, m_sFragmentShaderFilename.c_str()))
        return false;

    if (!Finalize())
        return false;

    m_wvpLocation = GetUniformLocation("gWVP");
	m_worldMatrixLocation = GetUniformLocation("gWorld");
    m_samplerLocation = GetUniformLocation("gSampler");
    m_dirLightLocation.m_color = GetUniformLocation("gDirectionalLight.Base.Color");
    m_dirLightLocation.m_ambientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
	m_dirLightLocation.m_direction = GetUniformLocation("gDirectionalLight.Direction");
    m_dirLightLocation.m_diffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
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
        return false;
    }

	for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_boneLocation) ; i++) {
        char name[128];
        memset(name, 0, sizeof(name));
        SNPRINTF(name, sizeof(name), "gBones[%d]", i);
        m_boneLocation[i] = GetUniformLocation(name);
    }

    return true;
}

void Light::SetWVP(Matrix _WVP)
{
	glUniformMatrix4fv(m_wvpLocation, 1, GL_FALSE,&_WVP.m_m[0]);    
}

void Light::SetWorldMatrix(Matrix _worldInverse)
{
	glUniformMatrix4fv(m_worldMatrixLocation, 1, GL_FALSE, &_worldInverse.m_m[0]);
}


void Light::SetTextureUnit(unsigned int _textureUnit)
{
    glUniform1i(m_samplerLocation, _textureUnit);
}


void Light::SetDirectionalLight(const DirectionalLight _light)
{
    glUniform3f(m_dirLightLocation.m_color, _light.m_color.m_fX, _light.m_color.m_fY, _light.m_color.m_fZ);
    glUniform1f(m_dirLightLocation.m_ambientIntensity, _light.m_fAmbientIntensity);
    Vector3 direction = _light.m_direction;
    direction = direction.Normalize();
    glUniform3f(m_dirLightLocation.m_direction, direction.m_fX, direction.m_fY, direction.m_fZ);
    glUniform1f(m_dirLightLocation.m_diffuseIntensity, _light.m_fDiffuseIntensity);
}

void Light::SetEyeWorldPos(const Vector3 _eyeWorldPos)
{
    glUniform3f(m_eyeWorldPosLocation, _eyeWorldPos.m_fX, _eyeWorldPos.m_fY, _eyeWorldPos.m_fZ);
}

void Light::SetMatSpecularIntensity(float _intensity)
{
    glUniform1f(m_matSpecularIntensityLocation, _intensity);
}

void Light::SetMatSpecularPower(float _power)
{
    glUniform1f(m_matSpecularPowerLocation, _power);
}

void Light::SetBoneTransform(uint _index, const Matrix _transform)
{
    assert(_index < MAX_BONES);
	glUniformMatrix4fv(m_boneLocation[_index], 1, GL_FALSE, &_transform.m_m[0]);       
}