#ifndef MESH_H
#define MESH_H

#include "vector3.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	Vector3 vertices[4];
	int indices[12];

};


#endif //MESH_H

