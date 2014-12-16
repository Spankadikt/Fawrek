#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
	float x,y,z;

	Vector3();
	Vector3(float _x, float _y, float _z);

	Vector3 operator+ (const Vector3 &_v);
	Vector3 operator- (const Vector3 &_v);
	Vector3 operator* (const Vector3 &_v);
	Vector3 operator/ (const Vector3 &_v);
	Vector3 operator+= (const Vector3 &_v);
	Vector3 operator-= (const Vector3 &_v);
	Vector3 operator*= (const Vector3 &_v);
	Vector3 operator/= (const Vector3 &_v);

	static Vector3 Cross(const Vector3 &_u, const Vector3 &_v);
	Vector3 Normalize() const;
	static float Dot(const Vector3 &_u, const Vector3 &_v);
};

#endif //VECTOR3_H