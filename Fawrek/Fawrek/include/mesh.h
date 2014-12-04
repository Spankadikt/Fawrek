#ifndef MESH_H
#define MESH_H

#include "vector3.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	Vector3 vertices[8];
	int indices[36];

};


#endif //MESH_H

