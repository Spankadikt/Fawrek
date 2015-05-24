#include "objectmanager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

Object* ObjectManager::GetObjectById(int _nId)
{
	for(int i=0; i<m_objects.size();i++)
	{
		if(m_objects[i]->m_id == _nId)
			return m_objects[i];
	}

	return 0;
}