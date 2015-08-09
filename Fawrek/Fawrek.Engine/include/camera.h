#include "api.h"

#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"
#include "matrix.h"
#include "object.h"

class FAWREK_API Camera : public Object
{
public:

    Camera();
    Camera(Vector3 _pos, Vector3 _target, Vector3 _up);
	~Camera();

	void PerspectiveFOV(float _fFovAngle, float _fAspectRation, float _fNearZ, float _fFarZ);
	void LookAt(Vector3 _pos, Vector3 _target, Vector3 _up);

	Matrix view;
	Matrix projection;

	float m_fFovAngle;
	float m_fAspectRation;
	float m_fNearZ;
	float m_fFarZ;
    Vector3 m_target;
    Vector3 m_up;

};

#endif	/* CAMERA_H */
