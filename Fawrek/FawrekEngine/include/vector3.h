#include "api.h"

#ifndef VECTOR3_H
#define VECTOR3_H

class FAWREK_API Vector3
{
public:
	float m_fX,m_fY,m_fZ;

	Vector3();
	Vector3(float _fX, float _fY, float _fZ);

	Vector3 operator*(const float _fS) const;
	Vector3 operator/(const float _fS) const;
	Vector3 operator+ (const Vector3& _v) const;
	Vector3 operator- (const Vector3& _v) const;
	Vector3 operator* (const Vector3& _v);
	Vector3 operator/ (const Vector3& _v);
	Vector3 operator+= (const Vector3& _v);
	Vector3 operator-= (const Vector3& _v);
	Vector3 operator*= (const Vector3& _v);
	Vector3 operator/= (const Vector3& _v);

	static Vector3 Cross(const Vector3& _u, const Vector3& _v);
	Vector3 Normalize() const;
	static float Dot(const Vector3& _u, const Vector3& _v);

    Vector3 Lerp(const Vector3& _from, const Vector3& _to, float _fTime);
};


#endif //VECTOR3_H