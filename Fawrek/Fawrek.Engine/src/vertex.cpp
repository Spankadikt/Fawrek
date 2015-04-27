#include "vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(Vector3 _position, Vector2 _uv, Vector3 _normal)
{
	m_position = _position;
	m_uv = _uv;
	m_normal = _normal;
}