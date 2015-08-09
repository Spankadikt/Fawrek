#include "directionallight.h"

DirectionalLight::DirectionalLight()
{
    m_direction = Vector3(0.0f, 0.0f, 0.0f);
}

DirectionalLight::DirectionalLight(Vector3 _direction)
{
	m_direction = _direction;
}

void DirectionalLight::SetDirection(float _fX, float _fY, float _fZ)
{
	Vector3 vec = Vector3(_fX, _fY, _fZ);
	m_direction = vec;
}