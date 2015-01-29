#include <math.h>

#include "vector3.h"

Vector3::Vector3()
{
}

Vector3::Vector3(float _fX, float _fY, float _fZ)
{
	m_fX = _fX;
	m_fY = _fY;
	m_fZ = _fZ;
}

// Scalar operation
Vector3 Vector3::operator*(const float _fS) const
{
	return Vector3(m_fX*_fS, m_fY*_fS, m_fZ*_fS);
}

Vector3 Vector3::operator/(const float _fS) const
{
	return (*this * (1.f / _fS));
}

Vector3 Vector3::operator+(const Vector3& _v) const
{
	return Vector3(m_fX + _v.m_fX, m_fY + _v.m_fY, m_fZ + _v.m_fZ);
}

Vector3 Vector3::operator-(const Vector3& _v) const
{
	return Vector3(m_fX - _v.m_fX, m_fY - _v.m_fY, m_fZ - _v.m_fZ);
}

Vector3 Vector3::operator*(const Vector3& _v)
{
	return Vector3(m_fX * _v.m_fX, m_fY * _v.m_fY, m_fZ * _v.m_fZ);
}

Vector3 Vector3::operator/(const Vector3& _v)
{
	return Vector3(m_fX / _v.m_fX, m_fY / _v.m_fY, m_fZ / _v.m_fZ);
}

Vector3 Vector3::operator*=(const Vector3& _v)
{
	m_fX *= _v.m_fX;
	m_fY *= _v.m_fY;
	m_fZ *= _v.m_fZ;
	return *this;
}

Vector3 Vector3::operator/=(const Vector3& _v)
{
	m_fX /= _v.m_fX;
	m_fY /= _v.m_fY;
	m_fZ /= _v.m_fZ;
	return *this;
}

Vector3 Vector3::operator+=(const Vector3& _v)
{
	m_fX += _v.m_fX;
	m_fY += _v.m_fY;
	m_fZ += _v.m_fZ;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3& _v)
{
	m_fX -= _v.m_fX;
	m_fY -= _v.m_fY;
	m_fZ -= _v.m_fZ;
	return *this;
}

Vector3 Vector3::Cross(const Vector3& _u,const Vector3& _v)
{
	Vector3 result;

    result.m_fX = _u.m_fY * _v.m_fZ - _u.m_fZ * _v.m_fY;
    result.m_fY = _u.m_fZ * _v.m_fX - _u.m_fX * _v.m_fZ;
    result.m_fZ = _u.m_fX * _v.m_fY - _u.m_fY * _v.m_fX;

    return result;
}

Vector3 Vector3::Normalize() const
{
	Vector3 result(m_fX,m_fY,m_fZ);

	const float Length = sqrtf(m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ);

    result.m_fX /= Length;
    result.m_fY /= Length;
    result.m_fZ /= Length;

    return result;
}

float Vector3::Dot(const Vector3& _u, const Vector3& _v)
{
	return _u.m_fX*_v.m_fX + _u.m_fY*_v.m_fY + _u.m_fZ*_v.m_fZ;
}

Vector3 Vector3::Lerp(const Vector3& _from, const Vector3& _to, float _fTime)
{
	Vector3 ret;
	ret = _from + (_to - _from)*_fTime;
	return ret;
}
