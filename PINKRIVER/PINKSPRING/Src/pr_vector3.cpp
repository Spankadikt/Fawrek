#include <math.h>

#include "pr_vector3.h"

Vector3::Vector3()
{
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3 &Vector3::operator+(const Vector3 &_v)
{
	return Vector3(x + _v.x, y + _v.y, z + _v.z);
}

Vector3 &Vector3::operator-(const Vector3 &_v)
{
	return Vector3(x - _v.x, y - _v.y, z - _v.z);
}

Vector3 &Vector3::operator*(const Vector3 &_v)
{
	return Vector3(x * _v.x, y * _v.y, z * _v.z);
}

Vector3 &Vector3::operator/(const Vector3 &_v)
{
	return Vector3(x / _v.x, y / _v.y, z / _v.z);
}

Vector3 *Vector3::Cross(const Vector3 &_u,const Vector3 &_v)
{
    float _x = _u.y * _v.z - _u.z * _v.y;
    float _y = _u.z * _v.x - _u.x * _v.z;
    float _z = _u.x * _v.y - _u.y * _v.x;

	Vector3 result = Vector3(_x,_y,_z);

    return &result;
}

Vector3 Vector3::Normalize() const
{
	Vector3 _v(x,y,z);

	const float Length = sqrtf(x * x + y * y + z * z);

    _v.x /= Length;
    _v.y /= Length;
    _v.z /= Length;

    return _v;
}

float Vector3::Dot(const Vector3 &_u, const Vector3 &_v)
{
	return _u.x*_v.x + _u.y*_v.y + _u.z*_v.z;
}