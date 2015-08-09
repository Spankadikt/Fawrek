#include <cmath>

#include "camera.h"
#include "utils.h"

Camera::Camera()
{
	m_translation = Vector3(-10.0f,10.0f,10.0f);
	m_target = Vector3(0.0f,0.0f,0.0f);
	m_up = Vector3(0.0f,1.0f,0.0f);
}

Camera::Camera(Vector3 _pos, Vector3 _target, Vector3 _up)
{
	m_translation = _pos;
	m_target = _target;
	m_up = _up;
}

Camera::~Camera()
{
}

void Camera::PerspectiveFOV(float _fFovAngle, float _fAspectRatio, float _fNearZ, float _fFarZ)
{
	m_fFovAngle = _fFovAngle;
	m_fAspectRation = _fAspectRatio;
	m_fNearZ = _fNearZ;
	m_fFarZ = _fFarZ;

	const float rad = std::tan(_fFovAngle * PI_f / 360.f);

	projection = Matrix::Zero;
	projection.m_m[ 0] = 1.f / (_fAspectRatio * rad);
	projection.m_m[ 5] = 1.f / rad;
	projection.m_m[10] = -(_fFarZ + _fNearZ) / (_fFarZ - _fNearZ);
	projection.m_m[11] = -1;
	projection.m_m[14] = -(2.f * _fFarZ * _fNearZ) / (_fFarZ - _fNearZ);
}

void Camera::LookAt(Vector3 _pos, Vector3 _target, Vector3 _up)
{
	m_translation = _pos;
	m_target = _target;
	m_up = _up;
	/*
	*		OpenGL MODELVIEW
	*		Column Major
	*	X.m_fX		Y.m_fX		Z.m_fX		T.m_fX
	*	X.m_fY		Y.m_fY		Z.m_fY		T.m_fY
	*	X.m_fZ		Y.m_fZ		Z.m_fZ		T.m_fZ
	*	-		-		-		-
	* X: Side
	* Y: Up
	* Z: Forward
	* T: Translation
	*/

	const Vector3 forward = (m_translation - m_target).Normalize();
	// Side = forward m_fX up
	const Vector3 side = (Vector3::Cross(m_up, forward)).Normalize();

	// Recompute up as: up = side m_fX forward
	const Vector3 rup = Vector3::Cross(forward, side);

	//Work on temp matrix
	Matrix result = Matrix::Identity;

	result.m_m[ 0] = side.m_fX;
	result.m_m[ 4] = side.m_fY;
	result.m_m[ 8] = side.m_fZ;

	result.m_m[ 1] = rup.m_fX;
	result.m_m[ 5] = rup.m_fY;
	result.m_m[ 9] = rup.m_fZ;

	result.m_m[ 2] = forward.m_fX;
	result.m_m[ 6] = forward.m_fY;
	result.m_m[10] = forward.m_fZ;

	result.m_m[12] = -Vector3::Dot(side, m_translation);
	result.m_m[13] = -Vector3::Dot(rup, m_translation);
	result.m_m[14] = -Vector3::Dot(forward, m_translation);

	view = result;
}
