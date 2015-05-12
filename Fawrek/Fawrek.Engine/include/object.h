#include "api.h"

#ifndef OBJECT_H
#define OBJECT_H

#include "vector3.h"

class FAWREK_API Object
{
public:
	Object();
	~Object();

	Vector3 m_scale;
	Vector3 m_rotate;
	Vector3 m_translate;
};
#endif//OBJECT_H