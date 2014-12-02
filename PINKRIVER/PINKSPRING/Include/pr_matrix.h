#if defined(PR_LIBRARY_EXPORT)
#   define PR_LIBRARY_EXPORT   __declspec(dllexport)
#else
#   define PR_LIBRARY_EXPORT   __declspec(dllimport)
#endif

#ifndef MATRIX_H
#define MATRIX_H

#include "pr_utils.h"

extern "C"
{
	PR_LIBRARY_EXPORT class Matrix
	{
	public:
		float m[16];

		PR_LIBRARY_EXPORT Matrix();
		PR_LIBRARY_EXPORT Matrix(const float m[16]);

		PR_LIBRARY_EXPORT static Matrix *Identity();
		PR_LIBRARY_EXPORT static Matrix *Zero();

		void SetMatrix(float _m[16]);

		PR_LIBRARY_EXPORT Matrix operator* (const Matrix &_m);

		PR_LIBRARY_EXPORT void Scale(float x,float y, float z);
		PR_LIBRARY_EXPORT void Rotate(float x, float y, float z);
		PR_LIBRARY_EXPORT void Translate(float x, float y, float z);
	};
}

#endif //MATRIX_H