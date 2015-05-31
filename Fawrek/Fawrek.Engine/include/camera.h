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

	Vector3 pos;
    Vector3 target;
    Vector3 up;

};

#endif	/* CAMERA_H */
