#include "api.h"

#ifndef BASELIGHT_H
#define BASELIGHT_H

#include "vector3.h"
#include "matrix.h"

class FAWREK_API BaseLight
{
public:
    BaseLight();
	BaseLight(float _fAmbientIntensity, float _fDiffuseIntensity, Vector3 _color);

	Vector3 m_color;
    float m_fAmbientIntensity;
    float m_fDiffuseIntensity;
};
#endif//BASELIGHT_H