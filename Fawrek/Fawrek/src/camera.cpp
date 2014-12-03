#include <cmath>

#include "camera.h"
#include "utils.h"

Camera::Camera()
{
	pos = Vector3(10.0f,0.0f,31.0f);
	target = Vector3(0.0f,0.0f,0.0f);
	up = Vector3(0.0f,1.0f,0.0f);
}

Camera::~Camera()
{
}

void Camera::PerspectiveFOV(float _fovAngle, float _aspectRatio, float _nearZ, float _farZ)
{
	const float rad = std::tan(_fovAngle * PI_f / 360.f);

	projection = Matrix::Zero;
	projection.m[ 0] = 1.f / (_aspectRatio * rad);
	projection.m[ 5] = 1.f / rad;
	projection.m[10] = -(_farZ + _nearZ) / (_farZ - _nearZ);
	projection.m[11] = -1;
	projection.m[14] = -(2.f * _farZ * _nearZ) / (_farZ - _nearZ);
}

void Camera::LookAt(Vector3 _pos, Vector3 _target, Vector3 _up)
{
	pos = _pos;
	target = _target;
	up = _up;
	/*
	*		OpenGL MODELVIEW
	*		Column Major
	*	X.x		Y.x		Z.x		T.x
	*	X.y		Y.y		Z.y		T.y
	*	X.z		Y.z		Z.z		T.z
	*	-		-		-		-
	* X: Side
	* Y: Up
	* Z: Forward
	* T: Translation
	*/

	const Vector3 forward = (pos - target).Normalize();
	// Side = forward x up
	const Vector3 side = (Vector3::Cross(up, forward)).Normalize();

	// Recompute up as: up = side x forward
	const Vector3 rup = Vector3::Cross(forward, side);

	//Work on temp matrix
	Matrix result = Matrix::Identity;

	result.m[ 0] = side.x;
	result.m[ 4] = side.y;
	result.m[ 8] = side.z;

	result.m[ 1] = rup.x;
	result.m[ 5] = rup.y;
	result.m[ 9] = rup.z;

	result.m[ 2] = forward.x;
	result.m[ 6] = forward.y;
	result.m[10] = forward.z;

	result.m[12] = -Vector3::Dot(side, pos);
	result.m[13] = -Vector3::Dot(rup, pos);
	result.m[14] = -Vector3::Dot(forward, pos);

	view = result;
}
