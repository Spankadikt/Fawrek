#ifndef MATRIX_H
#define MATRIX_H

#include "utils.h"
#include "vector3.h"

#include "assimp/vector3.h"
#include "matrix3x3.h"
#include "matrix4x4.h"

class Quaternion;

class Matrix
{
public:
	float m[16];

	Matrix();
	Matrix(const float _m[16]);
	Matrix(const aiMatrix3x3 &_assimpMatrix);
	Matrix(const aiMatrix4x4 &_assimpMatrix);

	static Matrix Identity;
	static Matrix Zero;

	Matrix operator* (const Matrix &_m) const;

	Matrix Scale(const Vector3 &_s);
	Matrix Scale(const float _s1,const float _s2,const float _s3);
	Matrix Rotate(const Quaternion &_q);
	//Matrix Rotate(const Matrix &_m);
	Matrix Translate(const Vector3 &_v);
	Matrix Translate(const float _v1,const float _v2,const float _v3);

	void GetRowMajor(float floatArray[16]);
	/// The transformation matrix that undoes this transformation.
	Matrix GetInverse() const;

    Matrix SetIdentity(float _value);

	void InitTranslationTransform(float x, float y, float z);
	void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);

	void SetZero()
    {
        ZERO_MEM(m);
    }
};

#endif //MATRIX_H