#include <iostream>

#include "pr_matrix.h"

Matrix::Matrix()
{
	// identity
	// | 1 0 0 0 |
	// | 0 1 0 0 |
	// | 0 0 1 0 |
	// | 0 0 0 1 |
	m[ 0] = 1;    m[ 4] = 0;    m[ 8] = 0;    m[12] = 0;
	m[ 1] = 0;    m[ 5] = 1;    m[ 9] = 0;    m[13] = 0;
	m[ 2] = 0;    m[ 6] = 0;    m[10] = 1;    m[14] = 0;
	m[ 3] = 0;    m[ 7] = 0;    m[11] = 0;    m[15] = 1;
}

Matrix::Matrix(const float _m[16])
{
	memcpy(m, _m, sizeof(float)*16);
}

Matrix *Matrix::Identity()
{
	Matrix _m;

	_m.m[ 0] = 1;    _m.m[ 4] = 0;    _m.m[ 8] = 0;    _m.m[12] = 0;
	_m.m[ 1] = 0;    _m.m[ 5] = 1;    _m.m[ 9] = 0;    _m.m[13] = 0;
	_m.m[ 2] = 0;    _m.m[ 6] = 0;    _m.m[10] = 1;    _m.m[14] = 0;
	_m.m[ 3] = 0;    _m.m[ 7] = 0;    _m.m[11] = 0;    _m.m[15] = 1;

	return &_m;
}

Matrix *Matrix::Zero()
{
	Matrix _m;

	_m.m[ 0] = 0;    _m.m[ 4] = 0;    _m.m[ 8] = 0;    _m.m[12] = 0;
	_m.m[ 1] = 0;    _m.m[ 5] = 0;    _m.m[ 9] = 0;    _m.m[13] = 0;
	_m.m[ 2] = 0;    _m.m[ 6] = 0;    _m.m[10] = 0;    _m.m[14] = 0;
	_m.m[ 3] = 0;    _m.m[ 7] = 0;    _m.m[11] = 0;    _m.m[15] = 0;

	return &_m;
}

Matrix Matrix::operator*(const Matrix &_m)
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

void Matrix::Scale(float ScaleX, float ScaleY, float ScaleZ)
{
    m[0] = ScaleX;	m[4] = 0.0f;	m[8] = 0.0f;	m[12] = 0.0f;
    m[1] = 0.0f;	m[5] = ScaleY;	m[9] = 0.0f;	m[13] = 0.0f;
    m[2] = 0.0f;	m[6] = 0.0f;	m[10] = ScaleZ;	m[14] = 0.0f;
    m[3] = 0.0f;	m[7] = 0.0f;	m[11] = 0.0f;	m[15] = 1.0f;
}

void Matrix::Rotate(float RotateX, float RotateY, float RotateZ)
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
}

void Matrix::Translate(float x, float y, float z)
{
    m[0] = 1.0f; m[4] = 0.0f; m[8] = 0.0f; m[12] = x;
    m[1] = 0.0f; m[5] = 1.0f; m[9] = 0.0f; m[13] = y;
    m[2] = 0.0f; m[6] = 0.0f; m[10] = 1.0f; m[14] = z;
    m[3] = 0.0f; m[7] = 0.0f; m[11] = 0.0f; m[15] = 1.0f;
}