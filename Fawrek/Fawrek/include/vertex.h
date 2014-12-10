#ifndef VERTEX_H
#define VERTEX_H

#include "vector3.h"
#include "vector2.h"

class Vertex
{
public :
	Vector3 position;
	Vector2 uv;
	Vector3 normal;

	Vertex();
	Vertex(Vector3 _pos, Vector2 _uv, Vector3 _normal);
};

#endif //VERTEX_H