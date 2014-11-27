#if defined(PR_LIBRARY_EXPORT)
#   define PR_LIBRARY_EXPORT   __declspec(dllexport)
#else
#   define PR_LIBRARY_EXPORT   __declspec(dllimport)
#endif

#ifndef MATRIX_H
#define MATRIX_H

extern "C"
{
	PR_LIBRARY_EXPORT class Matrix
	{
	public:
		float m[16];

		PR_LIBRARY_EXPORT Matrix();
		PR_LIBRARY_EXPORT Matrix(const float m[16]);
	};
}

#endif //MATRIX_H