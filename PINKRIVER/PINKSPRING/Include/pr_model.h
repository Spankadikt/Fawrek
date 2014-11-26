#if defined(PR_LIBRARY_EXPORT) // inside DLL
#   define PR_LIBRARY_EXPORT   __declspec(dllexport)
#else // outside DLL
#   define PR_LIBRARY_EXPORT   __declspec(dllimport)
#endif  // XYZLIBRARY_EXPORT

#include "pr_mesh.h"

PR_LIBRARY_EXPORT class Model
{
public:
	PR_LIBRARY_EXPORT Model();
	PR_LIBRARY_EXPORT ~Model();

	PR_LIBRARY_EXPORT Mesh *getMesh();

private:
	Mesh mesh;
};

