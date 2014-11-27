#if defined(PR_LIBRARY_EXPORT)
#   define PR_LIBRARY_EXPORT   __declspec(dllexport)
#else
#   define PR_LIBRARY_EXPORT   __declspec(dllimport)
#endif

#ifndef VECTOR3_H
#define VECTOR3_H

extern "C"
{
	PR_LIBRARY_EXPORT class Vector3
	{
	public:

		float x,y,z;

		PR_LIBRARY_EXPORT Vector3();
		PR_LIBRARY_EXPORT Vector3(float _x, float _y, float _z);
	};
}

#endif //VECTOR3_H