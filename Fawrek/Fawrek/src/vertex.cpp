#include "vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(Vector3 _position, Vector2 _uv, Vector3 _normal)
{
	position = _position;
	uv = _uv;
	normal = _normal;
}