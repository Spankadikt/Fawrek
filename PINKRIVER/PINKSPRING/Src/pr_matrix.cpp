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