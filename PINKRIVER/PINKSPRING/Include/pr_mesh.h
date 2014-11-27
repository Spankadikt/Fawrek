#if defined(PR_LIBRARY_EXPORT)
#   define PR_LIBRARY_EXPORT   __declspec(dllexport)
#else
#   define PR_LIBRARY_EXPORT   __declspec(dllimport)
#endif

#ifndef MESH_H
#define MESH_H

#include "pr_vector3.h"

extern "C"
{
	PR_LIBRARY_EXPORT class Mesh
	{
	public:
		PR_LIBRARY_EXPORT Mesh();
		PR_LIBRARY_EXPORT ~Mesh();

		PR_LIBRARY_EXPORT Vector3 *getVertices();
		PR_LIBRARY_EXPORT unsigned int *getIndices();

	private:
		Vector3 vertices[4];
		unsigned int indices[12];
	};
}

#endif //MESH_H

