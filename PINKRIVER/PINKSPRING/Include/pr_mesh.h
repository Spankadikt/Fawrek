#if defined(PR_LIBRARY_EXPORT) // inside DLL
#   define PR_LIBRARY_EXPORT   __declspec(dllexport)
#else // outside DLL
#   define PR_LIBRARY_EXPORT   __declspec(dllimport)
#endif  // XYZLIBRARY_EXPORT

#include "pr_maths.h"

extern "C"
{
PR_LIBRARY_EXPORT class Mesh
{
public:
	PR_LIBRARY_EXPORT Mesh();
	PR_LIBRARY_EXPORT ~Mesh();

	PR_LIBRARY_EXPORT Vector3 *getVertices();

private:
	Vector3 vertices[3];
};
}


