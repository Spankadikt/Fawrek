#ifndef QUATERNION_H
#define QUATERNION_H

#include "matrix.h"

class Quaternion
{
public:
	float x,y,z,w;

	Quaternion();
	Quaternion(float _x,float _y,float _z,float _w);

	Quaternion FromEuler(float yaw, float pitch, float roll);
	Quaternion FromMatrix(const Matrix _mat);
	Vector3 ToEuler() const;
	Matrix ToMatrix() const;
};

#endif //QUATERNION_H