#include <cmath>

#include "camera.h"
#include "pr_utils.h"

#define ToRadian(x) ((x) * PI_f / 180.0f)
#define ToDegree(x) ((x) * 180.0f / PI_f)

Camera::Camera()
{
}

Camera::Camera(const Vector3 _pos, const Vector3 _target, const Vector3 _up)
{
    pos = _pos;

    target = _target;
    target.Normalize();

    up = _up;
	target.Normalize();
}

Camera::~Camera()
{
}

void Camera::Set(Vector3 _pos, Vector3 _target, Vector3 _up)
{
	pos = _pos;
	target = _target;
	target.Normalize();
	up = _up;
	target.Normalize();
}

void Camera::PerspectiveFOV(float _fovAngle, float _aspectRatio, float _nearZ, float _farZ)
{
    const float zRange = _farZ - _nearZ ;
	const float tanHalfFOV = tanf(ToRadian((_fovAngle/2.0f)));

	Matrix _result = *Matrix::Zero();

	_result.m[0] = 1.0f / (tanHalfFOV * _aspectRatio);
	_result.m[5] = 1.0f / tanHalfFOV; 
	_result.m[10] = -(_farZ + _nearZ) / zRange; 
	_result.m[11] = -1;
	_result.m[14] = -(2.0f * _nearZ * _farZ)  / zRange;

	projection = _result;
}

void Camera::LookAt(Vector3 _pos, Vector3 _target, Vector3 _up)
{
	Vector3 N = _target;
    N.Normalize();
    Vector3 U = _up;
    U.Normalize();
    U = *Vector3::Cross(U,N);
	Vector3 V = *Vector3::Cross(N,U);

	Matrix _result = *Matrix::Identity();

    _result.m[0] = U.x;   _result.m[4] = U.y;   _result.m[8] = U.z;   _result.m[12] = 0.0f;
    _result.m[1] = V.x;   _result.m[5] = V.y;   _result.m[9] = V.z;   _result.m[13] = 0.0f;
    _result.m[2] = N.x;   _result.m[6] = N.y;   _result.m[10] = N.z;   _result.m[14] = 0.0f;
    _result.m[3] = 0.0f;  _result.m[7] = 0.0f;  _result.m[11] = 0.0f;  _result.m[15] = 1.0f;

	view = _result;
}
