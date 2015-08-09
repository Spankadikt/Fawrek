#include "api.h"

#ifndef BASELIGHT_H
#define BASELIGHT_H

#include "vector3.h"
#include "matrix.h"
#include "object.h"

class FAWREK_API BaseLight : public Object
{
public:
    BaseLight();
	BaseLight(float _fAmbientIntensity, float _fDiffuseIntensity, Vector3 _color);

	void SetColor(float _fR, float _fG, float _fB);

	Vector3 m_color;
    float m_fAmbientIntensity;
    float m_fDiffuseIntensity;
};
#endif//BASELIGHT_H