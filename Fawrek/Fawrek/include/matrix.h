#ifndef MATRIX_H
#define MATRIX_H

#include "utils.h"
#include "vector3.h"

class Quaternion;

class Matrix
{
public:
	float m[16];

	Matrix();
	Matrix(const float _m[16]);

	static Matrix Identity;
	static Matrix Zero;

	Matrix operator* (const Matrix &_m) const;

	Matrix Scale(const Vector3 &_s);
	Matrix Rotate(const Quaternion &_q);
	Matrix Translate(const Vector3 &_v);
};

#endif //MATRIX_H