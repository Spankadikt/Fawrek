#include <iostream>

#include "matrix.h"
#include "quaternion.h"

Matrix::Matrix()
{
}

Matrix::Matrix(const float _m[16])
{
	memcpy(m, _m, sizeof(float)*16);
}

// constructor from Assimp matrix
Matrix::Matrix(const aiMatrix4x4 &_assimpMatrix)
{
    m[0] = _assimpMatrix.a1; m[4] = _assimpMatrix.a2; m[8] = _assimpMatrix.a3; m[12] = _assimpMatrix.a4;
    m[1] = _assimpMatrix.b1; m[5] = _assimpMatrix.b2; m[9] = _assimpMatrix.b3; m[13] = _assimpMatrix.b4;
    m[2] = _assimpMatrix.c1; m[6] = _assimpMatrix.c2; m[10] = _assimpMatrix.c3; m[14] = _assimpMatrix.c4;
    m[3] = _assimpMatrix.d1; m[7] = _assimpMatrix.d2; m[11] = _assimpMatrix.d3; m[15] = _assimpMatrix.d4;
}
    
Matrix::Matrix(const aiMatrix3x3 &_assimpMatrix)
{
    m[0] = _assimpMatrix.a1; m[4] = _assimpMatrix.a2; m[8] = _assimpMatrix.a3; m[12] = 0.0f;
    m[1] = _assimpMatrix.b1; m[5] = _assimpMatrix.b2; m[9] = _assimpMatrix.b3; m[13] = 0.0f;
    m[2] = _assimpMatrix.c1; m[6] = _assimpMatrix.c2; m[10] = _assimpMatrix.c3; m[14] = 0.0f;
    m[3] = 0.0f           ;	m[7] = 0.0f           ;	m[11] = 0.0f           ;	m[15] = 1.0f;
}

const float __identity[16] =
{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};

Matrix Matrix::Identity(__identity);

const float __zero[16] =
{
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
};

Matrix Matrix::Zero(__zero);

Matrix Matrix::operator*(const Matrix &_m) const
{
	Matrix result;

	result.m[ 0]=m[ 0]*_m.m[ 0] + m[ 4]*_m.m[ 1] + m[ 8]*_m.m[ 2] + m[12]*_m.m[ 3];
	result.m[ 1]=m[ 1]*_m.m[ 0] + m[ 5]*_m.m[ 1] + m[ 9]*_m.m[ 2] + m[13]*_m.m[ 3];
	result.m[ 2]=m[ 2]*_m.m[ 0] + m[ 6]*_m.m[ 1] + m[10]*_m.m[ 2] + m[14]*_m.m[ 3];
	result.m[ 3]=m[ 3]*_m.m[ 0] + m[ 7]*_m.m[ 1] + m[11]*_m.m[ 2] + m[15]*_m.m[ 3];

	result.m[ 4]=m[ 0]*_m.m[ 4] + m[ 4]*_m.m[ 5] + m[ 8]*_m.m[ 6] + m[12]*_m.m[ 7];
	result.m[ 5]=m[ 1]*_m.m[ 4] + m[ 5]*_m.m[ 5] + m[ 9]*_m.m[ 6] + m[13]*_m.m[ 7];
	result.m[ 6]=m[ 2]*_m.m[ 4] + m[ 6]*_m.m[ 5] + m[10]*_m.m[ 6] + m[14]*_m.m[ 7];
	result.m[ 7]=m[ 3]*_m.m[ 4] + m[ 7]*_m.m[ 5] + m[11]*_m.m[ 6] + m[15]*_m.m[ 7];

	result.m[ 8]=m[ 0]*_m.m[ 8] + m[ 4]*_m.m[ 9] + m[ 8]*_m.m[10] + m[12]*_m.m[11];
	result.m[ 9]=m[ 1]*_m.m[ 8] + m[ 5]*_m.m[ 9] + m[ 9]*_m.m[10] + m[13]*_m.m[11];
	result.m[10]=m[ 2]*_m.m[ 8] + m[ 6]*_m.m[ 9] + m[10]*_m.m[10] + m[14]*_m.m[11];
	result.m[11]=m[ 3]*_m.m[ 8] + m[ 7]*_m.m[ 9] + m[11]*_m.m[10] + m[15]*_m.m[11];

	result.m[12]=m[ 0]*_m.m[12] + m[ 4]*_m.m[13] + m[ 8]*_m.m[14] + m[12]*_m.m[15];
	result.m[13]=m[ 1]*_m.m[12] + m[ 5]*_m.m[13] + m[ 9]*_m.m[14] + m[13]*_m.m[15];
	result.m[14]=m[ 2]*_m.m[12] + m[ 6]*_m.m[13] + m[10]*_m.m[14] + m[14]*_m.m[15];
	result.m[15]=m[ 3]*_m.m[12] + m[ 7]*_m.m[13] + m[11]*_m.m[14] + m[15]*_m.m[15];
	
	return result;
}

Matrix Matrix::Translate(const Vector3 &_v)
{
	m[12] = m[0] * _v.x + m[4] * _v.y + m[ 8] * _v.z + m[12];
	m[13] = m[1] * _v.x + m[5] * _v.y + m[ 9] * _v.z + m[13];
	m[14] = m[2] * _v.x + m[6] * _v.y + m[10] * _v.z + m[14];
	m[15] = m[3] * _v.x + m[7] * _v.y + m[11] * _v.z + m[15];

	return *this;
}

Matrix Matrix::Translate(const float _v1,const float _v2,const float _v3)
{
	m[12] = m[0] * _v1 + m[4] *  _v2 + m[ 8] * _v3 + m[12];
	m[13] = m[1] * _v1 + m[5] *  _v2 + m[ 9] * _v3 + m[13];
	m[14] = m[2] * _v1 + m[6] *  _v2 + m[10] * _v3 + m[14];
	m[15] = m[3] * _v1 + m[7] *  _v2 + m[11] * _v3 + m[15];

	return *this;
}

Matrix Matrix::Rotate(const Quaternion &_q)
{
	*this = operator*(_q.ToMatrix());
	return *this;
}

Matrix Matrix::Rotate(const Matrix &_m)
{
	*this = operator*(_m);
	return *this;
}

Matrix Matrix::Scale(const Vector3 &_s)
{
	m[0] *= _s.x;	m[4] *= _s.y;	m[ 8] *= _s.z;
    m[1] *= _s.x;	m[5] *= _s.y;	m[ 9] *= _s.z;
    m[2] *= _s.x;	m[6] *= _s.y;	m[10] *= _s.z;
    m[3] *= _s.x;	m[7] *= _s.y;	m[11] *= _s.z;

	return *this;
}

Matrix Matrix::Scale(const float _s1,const float _s2,const float _s3)
{
	m[0] *= _s1;	m[4] *= _s2;	m[ 8] *= _s3;
    m[1] *= _s1;	m[5] *= _s2;	m[ 9] *= _s3;
    m[2] *= _s1;	m[6] *= _s2;	m[10] *= _s3;
    m[3] *= _s1;	m[7] *= _s2;	m[11] *= _s3;

	return *this;
}

void Matrix::GetRowMajor(float floatArray[16])
{
	floatArray[ 0] = m[ 0];    floatArray[ 4] = m[ 1];    floatArray[ 8] = m[ 2];    floatArray[12] = m[ 3];
	floatArray[ 1] = m[ 4];    floatArray[ 5] = m[ 5];    floatArray[ 9] = m[ 6];    floatArray[13] = m[ 7];
	floatArray[ 2] = m[ 8];    floatArray[ 6] = m[ 9];    floatArray[10] = m[10];    floatArray[14] = m[11];
	floatArray[ 3] = m[12];    floatArray[ 7] = m[13];    floatArray[11] = m[14];    floatArray[15] = m[15];
}

Matrix Matrix::GetInverse() const
{
	Matrix ret;
	// Transpose the rotation Matrix
	ret.m[ 0] = m[ 0];		ret.m[ 4] = m[ 1];		ret.m[ 8] = m[ 2];
	ret.m[ 1] = m[ 4];		ret.m[ 5] = m[ 5];		ret.m[ 9] = m[ 6];
	ret.m[ 2] = m[ 8];		ret.m[ 6] = m[ 9];		ret.m[10] = m[10];

	// This is right, but it causes data to be copied for the negate, and we can make it slightly more efficient
	// by unrolling it
	// ret.Pos() = -ret.Rotate(Pos());

	ret.m[12]=-(ret.m[ 0]*m[12] + ret.m[ 4]*m[13] + ret.m[ 8]*m[14]);
	ret.m[13]=-(ret.m[ 1]*m[12] + ret.m[ 5]*m[13] + ret.m[ 9]*m[14]);
	ret.m[14]=-(ret.m[ 2]*m[12] + ret.m[ 6]*m[13] + ret.m[10]*m[14]);

	return ret;
}