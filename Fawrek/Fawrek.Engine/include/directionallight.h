#include "api.h"

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "baselight.h"

class FAWREK_API DirectionalLight : public BaseLight
{
public:
    DirectionalLight();
	DirectionalLight(Vector3 _direction);

	void SetDirection(float _fX, float _fY, float _fZ);

	Vector3 m_direction;
};
#endif//DIRECTIONALLIGHT_H