#include <math.h>

#include "vector3.h"

Vector3::Vector3()
{
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

// Scalar operation
Vector3 Vector3::operator*(const float s) const
{
	return Vector3(x*s, y*s, z*s);
}

Vector3 Vector3::operator/(const float s) const
{
	return (*this * (1.f / s));
}

Vector3 Vector3::operator+(const Vector3 &_v)
{
	return Vector3(x + _v.x, y + _v.y, z + _v.z);
}

Vector3 Vector3::operator-(const Vector3 &_v)
{
	return Vector3(x - _v.x, y - _v.y, z - _v.z);
}

Vector3 Vector3::operator*(const Vector3 &_v)
{
	return Vector3(x * _v.x, y * _v.y, z * _v.z);
}

Vector3 Vector3::operator/(const Vector3 &_v)
{
	return Vector3(x / _v.x, y / _v.y, z / _v.z);
}

Vector3 Vector3::operator*=(const Vector3 &_v)
{
	x *= _v.x;
	y *= _v.y;
	z *= _v.z;
	return *this;
}

Vector3 Vector3::operator/=(const Vector3 &_v)
{
	x /= _v.x;
	y /= _v.y;
	z /= _v.z;
	return *this;
}

Vector3 Vector3::operator+=(const Vector3 &_v)
{
	x += _v.x;
	y += _v.y;
	z += _v.z;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3 &_v)
{
	x -= _v.x;
	y -= _v.y;
	z -= _v.z;
	return *this;
}

Vector3 Vector3::Cross(const Vector3 &_u,const Vector3 &_v)
{
	Vector3 result;

    result.x = _u.y * _v.z - _u.z * _v.y;
    result.y = _u.z * _v.x - _u.x * _v.z;
    result.z = _u.x * _v.y - _u.y * _v.x;

    return result;
}

Vector3 Vector3::Normalize() const
{
	Vector3 result(x,y,z);

	const float Length = sqrtf(x * x + y * y + z * z);

    result.x /= Length;
    result.y /= Length;
    result.z /= Length;

    return result;
}

float Vector3::Dot(const Vector3 &u, const Vector3 &v)
{
	return u.x*v.x + u.y*v.y + u.z*v.z;
}
