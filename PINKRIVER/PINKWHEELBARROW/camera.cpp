#include <cmath>

#include "camera.h"

Camera::Camera()
{
}

Camera::Camera(const Vector3 _pos, const Vector3 _target, const Vector3 _up)
{
    pos = _pos;

    target = _target;
    target.Normalize();

    up = _up;
    up.Normalize();

}

Camera::~Camera()
{
}

void Camera::Set(Vector3 _pos, Vector3 _target, Vector3 _up)
{
	pos = _pos;
	target = _target;
	up = _up;
}

void Camera::PerspectiveFOV(float _fovAngle, float _aspectRatio, float _nearZ, float _farZ)
{
	const float rad = std::tan(_fovAngle * 3.14f / 360.f);

	Matrix _result = *Matrix::Zero();

	projection.m[0] = 1.f / (_aspectRatio * rad);
	projection.m[5] = 1.f / rad;
	projection.m[10] = -(_farZ + _nearZ) / (_farZ - _nearZ);
	projection.m[11] = -1;
	projection.m[14] = -(2.f * _farZ * _nearZ) / (_farZ - _nearZ);

	projection = _result;
}

void Camera::LookAt(Vector3 _pos, Vector3 _target, Vector3 _up)
{
	Vector3 _forward = (_pos - _target).Normalize();
	Vector3 _right = *Vector3::Cross(_up, _forward);
	_right = _right.Normalize();
	Vector3 _rup = *Vector3::Cross(_forward, _right);
	_rup = _rup.Normalize();

	Matrix _result = *Matrix::Identity();

	_result.m[0] = _right.x;
	_result.m[1] = _right.y;
	_result.m[2] = _right.z;
	_result.m[3] = -Vector3::Dot(_right, _pos);

	_result.m[4] = _rup.x;
	_result.m[5] = _rup.y;
	_result.m[6] = _rup.z;
	_result.m[7] = -Vector3::Dot(_rup, _pos);

	_result.m[8] = _forward.x;
	_result.m[9] = _forward.y;
	_result.m[10] = _forward.z;
	_result.m[11] = -Vector3::Dot(_forward, _pos);

	view = _result;
}
