#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"
#include "matrix.h"

class Camera
{
public:

    Camera();
    Camera(const Vector3 _pos, const Vector3 _target, const Vector3 _up);
	~Camera();

	void PerspectiveFOV(float _fovAngle, float _aspectRation, float _nearZ, float _farZ);
	void LookAt(Vector3 _pos, Vector3 _target, Vector3 _up);

	Matrix view;
	Matrix projection;

	Vector3 pos;
    Vector3 target;
    Vector3 up;

};

#endif	/* CAMERA_H */
