#include "api.h"

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "baselight.h"

class FAWREK_API DirectionalLight : public BaseLight
{
public:
    DirectionalLight();
	DirectionalLight(Vector3 _direction);

	Vector3 m_direction;
};
#endif//DIRECTIONALLIGHT_H