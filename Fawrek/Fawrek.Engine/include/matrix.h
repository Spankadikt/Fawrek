#include "api.h"

#ifndef MATRIX_H
#define MATRIX_H

#include "utils.h"
#include "vector3.h"

#include "assimp/vector3.h"
#include "assimp/matrix3x3.h"
#include "assimp/matrix4x4.h"

class Quaternion;

class FAWREK_API Matrix
{
public:
	float m_m[16];

	Matrix();
	Matrix(const float _m[16]);
	Matrix(const aiMatrix3x3& _assimpMatrix);
	Matrix(const aiMatrix4x4& _assimpMatrix);

	const static Matrix Identity;
	const static Matrix Zero;

	Matrix operator* (const Matrix& _m) const;
    Matrix& operator*=(const Matrix& _m);

	Matrix Scale(const Vector3& _s);
	Matrix Scale(const float _fS1,const float _fS2,const float _fS3);
	Matrix Rotate(const Quaternion& _q);
	Matrix Translate(const Vector3& _v);
	Matrix Translate(const float _fV1,const float _fV2,const float _fV3);

	void GetRowMajor(float _floatArray[16]);
	/// The transformation matrix that undoes this transformation.
	Matrix GetInverse() const;

    Matrix SetIdentity(float _fValue);

	void InitTranslationTransform(float _fX, float _fY, float _fZ);
	void InitScaleTransform(float _fScaleX, float _fScaleY, float _fScaleZ);

	void SetZero()
    {
        ZERO_MEM(m_m);
    }
};

#endif //MATRIX_H