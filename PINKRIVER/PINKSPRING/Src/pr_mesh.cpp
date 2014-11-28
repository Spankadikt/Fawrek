#include "pr_mesh.h"

Mesh::Mesh()
{
	vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);
    vertices[1] = Vector3(0.0f, -1.0f, 1.0f);
    vertices[2] = Vector3(1.0f, -1.0f, 0.0f);
    vertices[3] = Vector3(0.0f, 1.0f, 0.0f);

	indices[0] = 0;		indices[1] = 3;		indices[2] = 1;
	indices[3] = 1;		indices[4] = 3;		indices[5] = 2;
	indices[6] = 2;		indices[7] = 3;		indices[8] = 0;
	indices[9] = 0;		indices[10] = 1;	indices[11] = 2;      
                               
}

Mesh::~Mesh()
{
}

Vector3 *Mesh::getVertices()
{
	return vertices;
}

unsigned int *Mesh::getIndices()
{
	return indices;
}