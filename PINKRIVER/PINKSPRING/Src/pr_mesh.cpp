#include "pr_mesh.h"

Mesh::Mesh()
{
	vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);
    vertices[1] = Vector3(0.0f, -1.0f, 1.0f);
    vertices[2] = Vector3(1.0f, -1.0f, 0.0f);
    vertices[3] = Vector3(0.0f, 1.0f, 0.0f);

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