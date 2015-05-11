#include "directionallight.h"

DirectionalLight::DirectionalLight()
{
    m_direction = Vector3(0.0f, 0.0f, 0.0f);
}

DirectionalLight::DirectionalLight(Vector3 _direction)
{
	m_direction = _direction;
}