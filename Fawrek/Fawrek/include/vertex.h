#ifndef VERTEX_H
#define VERTEX_H

#include "vector3.h"
#include "vector2.h"

class Vertex
{
public :
	Vector3 pos;
	Vector2 uv;

	Vertex();
	Vertex(Vector3 _pos, Vector2 _uv);
};

#endif //VERTEX_H