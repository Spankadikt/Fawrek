#include "api.h"

#ifndef OBJECTMANAGER_H
#define	OBJECTMANAGER_H

#include "list"
#include "map"
#include "vector"
#include "utils.h"
#include "object.h"

class FAWREK_API ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	Object* GetObjectById(int _nId);

	vector<Object*> m_objects;
};
#endif OBJECTMANAGER_H
