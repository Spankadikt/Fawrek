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

/*void Matrix::Rotate(float RotateX, float RotateY, float RotateZ)
{
    Matrix rx, ry, rz;

	float x = tanf(ToRadian(RotateX));
    float y = tanf(ToRadian(RotateY));
    float z = tanf(ToRadian(RotateZ));

    rx.m[0] = 1.0f;			rx.m[4] = 0.0f   ;		rx.m[8] = 0.0f    ;		rx.m[12] = 0.0f;
    rx.m[1] = 0.0f;			rx.m[5] = cosf(x);		rx.m[9] = -sinf(x);		rx.m[13] = 0.0f;
    rx.m[2] = 0.0f;			rx.m[6] = sinf(x);		rx.m[10] = cosf(x) ;	rx.m[14] = 0.0f;
    rx.m[3] = 0.0f;			rx.m[7] = 0.0f   ;		rx.m[11] = 0.0f    ;	rx.m[15] = 1.0f;

    ry.m[0] = cosf(y);		ry.m[4] = 0.0f;			ry.m[8] = sinf(y);		ry.m[12] = 0.0f;
    ry.m[1] = 0.0f   ;		ry.m[5] = 1.0f;			ry.m[9] = 0.0f    ;		ry.m[13] = 0.0f;
    ry.m[2] = -sinf(y);		ry.m[6] = 0.0f;			ry.m[10] = cosf(y) ;	ry.m[14] = 0.0f;
    ry.m[3] = 0.0f   ;		ry.m[7] = 0.0f;			ry.m[11] = 0.0f    ;	ry.m[15] = 1.0f;

    rz.m[0] = cosf(z);		rz.m[4] = -sinf(z);		rz.m[8] = 0.0f;			rz.m[12] = 0.0f;
    rz.m[1] = sinf(z);		rz.m[5] = cosf(z) ;		rz.m[9] = 0.0f;			rz.m[13] = 0.0f;
    rz.m[2] = 0.0f   ;		rz.m[6] = 0.0f    ;		rz.m[10] = 1.0f;		rz.m[14] = 0.0f;
    rz.m[3] = 0.0f   ;		rz.m[7] = 0.0f    ;		rz.m[11] = 0.0f;		rz.m[15] = 1.0f;

	*this = rz * ry * rx;
}*/

Matrix Matrix::Translate(const Vector3 &_v)
{
	m[12] = m[0] * _v.x + m[4] * _v.y + m[ 8] * _v.z + m[12];
	m[13] = m[1] * _v.x + m[5] * _v.y + m[ 9] * _v.z + m[13];
	m[14] = m[2] * _v.x + m[6] * _v.y + m[10] * _v.z + m[14];
	m[15] = m[3] * _v.x + m[7] * _v.y + m[11] * _v.z + m[15];

	return *this;
}

Matrix Matrix::Rotate(const Quaternion &_q)
{
	*this = operator*(_q.ToMatrix());
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