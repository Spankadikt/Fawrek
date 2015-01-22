#ifndef VERTEX_H
#define VERTEX_H

#include "vector3.h"
#include "vector2.h"

class Vertex
{
public :
	Vector3 m_position;
	Vector2 m_uv;
	Vector3 m_normal;

	Vertex();
	Vertex(Vector3 _pos, Vector2 _uv, Vector3 _normal);
};

#endif //VERTEX_H