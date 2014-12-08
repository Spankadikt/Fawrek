#ifndef MESH_H
#define MESH_H

#include "vertex.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	Vertex vertices[8];
	int indices[36];

};


#endif //MESH_H

