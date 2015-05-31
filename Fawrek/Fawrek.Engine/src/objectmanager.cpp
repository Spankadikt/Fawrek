#include "objectmanager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

vector<Model*> ObjectManager::GetModels()
{
	vector<Model*> lstModel;
	for(int i=0; i<m_objects.size();i++)
	{
		Model* pModel = dynamic_cast<Model*>(m_objects[i]);
		if(pModel)
			lstModel.push_back(pModel);
	}

	return lstModel;
}

DirectionalLight* ObjectManager::GetDirectionalLight()
{
	for(int i=0; i<m_objects.size();i++)
	{
		DirectionalLight* pDirectionalLight = dynamic_cast<DirectionalLight*>(m_objects[i]);
		if(pDirectionalLight)
			return pDirectionalLight;
	}

	return 0;
}

Camera* ObjectManager::GetCamera()
{
	for(int i=0; i<m_objects.size();i++)
	{
		Camera* pCamera = dynamic_cast<Camera*>(m_objects[i]);
		if(pCamera)
			return pCamera;
	}

	return 0;
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