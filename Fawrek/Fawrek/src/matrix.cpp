#include <iostream>

#include "matrix.h"
#include "quaternion.h"

Matrix::Matrix()
{
	*this = Matrix::Identity;
}

Matrix::Matrix(const float _m[16])
{
	memcpy(m_m, _m, sizeof(float)*16);
}

// constructor from Assimp matrix
Matrix::Matrix(const aiMatrix4x4& _assimpMatrix)
{
    m_m[0] = _assimpMatrix.a1; m_m[4] = _assimpMatrix.a2; m_m[8] = _assimpMatrix.a3;    m_m[12] = _assimpMatrix.a4;
    m_m[1] = _assimpMatrix.b1; m_m[5] = _assimpMatrix.b2; m_m[9] = _assimpMatrix.b3;    m_m[13] = _assimpMatrix.b4;
    m_m[2] = _assimpMatrix.c1; m_m[6] = _assimpMatrix.c2; m_m[10] = _assimpMatrix.c3;   m_m[14] = _assimpMatrix.c4;
    m_m[3] = _assimpMatrix.d1; m_m[7] = _assimpMatrix.d2; m_m[11] = _assimpMatrix.d3;   m_m[15] = _assimpMatrix.d4;
}
    
Matrix::Matrix(const aiMatrix3x3& _assimpMatrix)
{
    m_m[0] = _assimpMatrix.a1;  m_m[4] = _assimpMatrix.a2;  m_m[8] = _assimpMatrix.a3;  m_m[12] = 0.0f;
    m_m[1] = _assimpMatrix.b1;  m_m[5] = _assimpMatrix.b2;  m_m[9] = _assimpMatrix.b3;  m_m[13] = 0.0f;
    m_m[2] = _assimpMatrix.c1;  m_m[6] = _assimpMatrix.c2;  m_m[10] = _assimpMatrix.c3; m_m[14] = 0.0f;
    m_m[3] = 0.0f           ;	m_m[7] = 0.0f           ;   m_m[11] = 0.0f           ;	m_m[15] = 1.0f;
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

Matrix Matrix::operator*(const Matrix& _m) const
{
	Matrix result;

	result.m_m[ 0] = m_m[ 0]*_m.m_m[ 0] + m_m[ 4]*_m.m_m[ 1] + m_m[ 8]*_m.m_m[ 2] + m_m[12]*_m.m_m[ 3];
	result.m_m[ 1] = m_m[ 1]*_m.m_m[ 0] + m_m[ 5]*_m.m_m[ 1] + m_m[ 9]*_m.m_m[ 2] + m_m[13]*_m.m_m[ 3];
	result.m_m[ 2] = m_m[ 2]*_m.m_m[ 0] + m_m[ 6]*_m.m_m[ 1] + m_m[10]*_m.m_m[ 2] + m_m[14]*_m.m_m[ 3];
	result.m_m[ 3] = m_m[ 3]*_m.m_m[ 0] + m_m[ 7]*_m.m_m[ 1] + m_m[11]*_m.m_m[ 2] + m_m[15]*_m.m_m[ 3];

	result.m_m[ 4] = m_m[ 0]*_m.m_m[ 4] + m_m[ 4]*_m.m_m[ 5] + m_m[ 8]*_m.m_m[ 6] + m_m[12]*_m.m_m[ 7];
	result.m_m[ 5] = m_m[ 1]*_m.m_m[ 4] + m_m[ 5]*_m.m_m[ 5] + m_m[ 9]*_m.m_m[ 6] + m_m[13]*_m.m_m[ 7];
	result.m_m[ 6] = m_m[ 2]*_m.m_m[ 4] + m_m[ 6]*_m.m_m[ 5] + m_m[10]*_m.m_m[ 6] + m_m[14]*_m.m_m[ 7];
	result.m_m[ 7] = m_m[ 3]*_m.m_m[ 4] + m_m[ 7]*_m.m_m[ 5] + m_m[11]*_m.m_m[ 6] + m_m[15]*_m.m_m[ 7];

	result.m_m[ 8] = m_m[ 0]*_m.m_m[ 8] + m_m[ 4]*_m.m_m[ 9] + m_m[ 8]*_m.m_m[10] + m_m[12]*_m.m_m[11];
	result.m_m[ 9] = m_m[ 1]*_m.m_m[ 8] + m_m[ 5]*_m.m_m[ 9] + m_m[ 9]*_m.m_m[10] + m_m[13]*_m.m_m[11];
	result.m_m[10] = m_m[ 2]*_m.m_m[ 8] + m_m[ 6]*_m.m_m[ 9] + m_m[10]*_m.m_m[10] + m_m[14]*_m.m_m[11];
	result.m_m[11] = m_m[ 3]*_m.m_m[ 8] + m_m[ 7]*_m.m_m[ 9] + m_m[11]*_m.m_m[10] + m_m[15]*_m.m_m[11];

	result.m_m[12] = m_m[ 0]*_m.m_m[12] + m_m[ 4]*_m.m_m[13] + m_m[ 8]*_m.m_m[14] + m_m[12]*_m.m_m[15];
	result.m_m[13] = m_m[ 1]*_m.m_m[12] + m_m[ 5]*_m.m_m[13] + m_m[ 9]*_m.m_m[14] + m_m[13]*_m.m_m[15];
	result.m_m[14] = m_m[ 2]*_m.m_m[12] + m_m[ 6]*_m.m_m[13] + m_m[10]*_m.m_m[14] + m_m[14]*_m.m_m[15];
	result.m_m[15] = m_m[ 3]*_m.m_m[12] + m_m[ 7]*_m.m_m[13] + m_m[11]*_m.m_m[14] + m_m[15]*_m.m_m[15];
	
	return result;
}

Matrix Matrix::Translate(const Vector3& _v)
{
	m_m[12] = m_m[0] * _v.m_fX + m_m[4] * _v.m_fY + m_m[ 8] * _v.m_fZ + m_m[12];
	m_m[13] = m_m[1] * _v.m_fX + m_m[5] * _v.m_fY + m_m[ 9] * _v.m_fZ + m_m[13];
	m_m[14] = m_m[2] * _v.m_fX + m_m[6] * _v.m_fY + m_m[10] * _v.m_fZ + m_m[14];
	m_m[15] = m_m[3] * _v.m_fX + m_m[7] * _v.m_fY + m_m[11] * _v.m_fZ + m_m[15];

	return *this;
}

Matrix Matrix::Translate(const float _v1,const float _v2,const float _v3)
{
	m_m[12] = m_m[0] * _v1 + m_m[4] *  _v2 + m_m[ 8] * _v3 + m_m[12];
	m_m[13] = m_m[1] * _v1 + m_m[5] *  _v2 + m_m[ 9] * _v3 + m_m[13];
	m_m[14] = m_m[2] * _v1 + m_m[6] *  _v2 + m_m[10] * _v3 + m_m[14];
	m_m[15] = m_m[3] * _v1 + m_m[7] *  _v2 + m_m[11] * _v3 + m_m[15];

	return *this;
}

Matrix Matrix::Rotate(const Quaternion& _q)
{
	*this = operator*(_q.ToMatrix());
	return *this;
}

Matrix Matrix::Scale(const Vector3 &_s)
{
	m_m[0] *= _s.m_fX;	m_m[4] *= _s.m_fY;	m_m[ 8] *= _s.m_fZ;
    m_m[1] *= _s.m_fX;	m_m[5] *= _s.m_fY;	m_m[ 9] *= _s.m_fZ;
    m_m[2] *= _s.m_fX;	m_m[6] *= _s.m_fY;	m_m[10] *= _s.m_fZ;
    m_m[3] *= _s.m_fX;	m_m[7] *= _s.m_fY;	m_m[11] *= _s.m_fZ;

	return *this;
}

Matrix Matrix::Scale(const float _s1,const float _s2,const float _s3)
{
	m_m[0] *= _s1;	m_m[4] *= _s2;	m_m[ 8] *= _s3;
    m_m[1] *= _s1;	m_m[5] *= _s2;	m_m[ 9] *= _s3;
    m_m[2] *= _s1;	m_m[6] *= _s2;	m_m[10] *= _s3;
    m_m[3] *= _s1;	m_m[7] *= _s2;	m_m[11] *= _s3;

	return *this;
}

void Matrix::GetRowMajor(float floatArray[16])
{
	floatArray[ 0] = m_m[ 0];    floatArray[ 4] = m_m[ 1];    floatArray[ 8] = m_m[ 2];    floatArray[12] = m_m[ 3];
	floatArray[ 1] = m_m[ 4];    floatArray[ 5] = m_m[ 5];    floatArray[ 9] = m_m[ 6];    floatArray[13] = m_m[ 7];
	floatArray[ 2] = m_m[ 8];    floatArray[ 6] = m_m[ 9];    floatArray[10] = m_m[10];    floatArray[14] = m_m[11];
	floatArray[ 3] = m_m[12];    floatArray[ 7] = m_m[13];    floatArray[11] = m_m[14];    floatArray[15] = m_m[15];
}

Matrix Matrix::GetInverse() const
{
	Matrix ret;
	// Transpose the rotation Matrix
	ret.m_m[ 0] = m_m[ 0];		ret.m_m[ 4] = m_m[ 1];		ret.m_m[ 8] = m_m[ 2];
	ret.m_m[ 1] = m_m[ 4];		ret.m_m[ 5] = m_m[ 5];		ret.m_m[ 9] = m_m[ 6];
	ret.m_m[ 2] = m_m[ 8];		ret.m_m[ 6] = m_m[ 9];		ret.m_m[10] = m_m[10];

	// This is right, but it causes data to be copied for the negate, and we can make it slightly more efficient
	// by unrolling it
	// ret.Pos() = -ret.Rotate(Pos());

	ret.m_m[12]=-(ret.m_m[ 0]*m_m[12] + ret.m_m[ 4]*m_m[13] + ret.m_m[ 8]*m_m[14]);
	ret.m_m[13]=-(ret.m_m[ 1]*m_m[12] + ret.m_m[ 5]*m_m[13] + ret.m_m[ 9]*m_m[14]);
	ret.m_m[14]=-(ret.m_m[ 2]*m_m[12] + ret.m_m[ 6]*m_m[13] + ret.m_m[10]*m_m[14]);

	return ret;
}

Matrix Matrix::SetIdentity(float _value)
{
    m_m[0] = _value;	m_m[4] = 0;	        m_m[ 8] = 0;          m_m[12] = 0;
    m_m[1] = 0;	    m_m[5] = _value;	    m_m[ 9] = 0;          m_m[13] = 0;
    m_m[2] = 0;	    m_m[6] = 0;	        m_m[10] = _value;     m_m[14] = 0;
    m_m[3] = 0;	    m_m[7] = 0;	        m_m[11] = 0;          m_m[15] = _value;

    return *this;
}


void Matrix::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ)
{
    m_m[0] = ScaleX; m_m[4] = 0.0f;   m_m[8] = 0.0f;   m_m[12] = 0.0f;
    m_m[1] = 0.0f;   m_m[5] = ScaleY; m_m[9] = 0.0f;   m_m[13] = 0.0f;
    m_m[2] = 0.0f;   m_m[6] = 0.0f;   m_m[10] = ScaleZ; m_m[14] = 0.0f;
    m_m[3] = 0.0f;   m_m[7] = 0.0f;   m_m[11] = 0.0f;   m_m[15] = 1.0f;
}


void Matrix::InitTranslationTransform(float m_fX, float m_fY, float m_fZ)
{
    m_m[0] = 1.0f; m_m[4] = 0.0f; m_m[8] = 0.0f; m_m[12] = m_fX;
    m_m[1] = 0.0f; m_m[5] = 1.0f; m_m[9] = 0.0f; m_m[13] = m_fY;
    m_m[2] = 0.0f; m_m[6] = 0.0f; m_m[10] = 1.0f; m_m[14] = m_fZ;
    m_m[3] = 0.0f; m_m[7] = 0.0f; m_m[11] = 0.0f; m_m[15] = 1.0f;
}