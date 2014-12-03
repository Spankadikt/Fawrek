#include <math.h>

#include "quaternion.h"

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Matrix Quaternion::ToMatrix() const
{
	const Quaternion &q = *this;

	float xx = q.x*q.x;
	float xy = q.x*q.y;
	float xz = q.x*q.z;
	float xw = q.x*q.w;

	float yy = q.y*q.y;
	float yz = q.y*q.z;
	float yw = q.y*q.w;

	float zz = q.z*q.z;
	float zw = q.z*q.w;

	Matrix result;

	result.m[0] = 1.f - 2.f * ( yy + zz );	result.m[4] = 2.f * ( xy + zw );		result.m[8] = 2.f * ( xz - yw );		result.m[12] = 0.f;
	result.m[1] = 2.f * ( xy - zw );		result.m[5] = 1.f - 2.f * ( xx + zz );	result.m[9] = 2.f * ( yz + xw );		result.m[13] = 0.f;
	result.m[2] = 2.f * ( xz + yw );		result.m[6] = 2.f * ( yz - xw );		result.m[10] = 1.f - 2.f * ( xx + yy );	result.m[14] = 0.f;
	result.m[3] = 0.f;						result.m[7] = 0.f;						result.m[11] = 0.f;						result.m[15] = 1.f;	

	return result;
}
