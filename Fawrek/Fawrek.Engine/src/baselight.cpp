#include "baselight.h"

BaseLight::BaseLight()
{
    m_color = Vector3(0.0f, 0.0f, 0.0f);
    m_fAmbientIntensity = 0.0f;
    m_fDiffuseIntensity = 0.0f;
}

BaseLight::BaseLight(float _fAmbientIntensity, float _fDiffuseIntensity, Vector3 _color)
{
    m_color = _color;
	m_fAmbientIntensity = _fAmbientIntensity;
	m_fDiffuseIntensity = _fDiffuseIntensity;
}

void BaseLight::SetColor(float _fR, float _fG, float _fB)
{
	Vector3 vec = Vector3(_fR, _fG, _fB);
	m_color = vec;
}