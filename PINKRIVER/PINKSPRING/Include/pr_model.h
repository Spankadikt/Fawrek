#if defined(PR_LIBRARY_EXPORT)
#   define PR_LIBRARY_EXPORT   __declspec(dllexport)
#else
#   define PR_LIBRARY_EXPORT   __declspec(dllimport)
#endif

#ifndef MODEL_H
#define MODEL_H

#include "pr_mesh.h"

extern "C"
{
	PR_LIBRARY_EXPORT class Model
	{
	public:
		PR_LIBRARY_EXPORT Model();
		PR_LIBRARY_EXPORT ~Model();

		PR_LIBRARY_EXPORT Mesh *getMesh();

	private:
		Mesh mesh;
	};
}

#endif //MESH_H

