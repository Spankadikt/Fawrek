#include "api.h"

#ifndef OBJECTMANAGER_H
#define	OBJECTMANAGER_H

#include "list"
#include "map"
#include "vector"
#include "utils.h"
#include "model.h"
#include "character.h"
#include "directionallight.h"
#include "camera.h"

class FAWREK_API ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	vector<Model*> GetModels();
	vector<Character*> GetCharacters();
	DirectionalLight* GetDirectionalLight();
	Camera* GetCamera();
	Object* GetObjectById(int _nId);

	vector<Object*> m_objects;
};
#endif OBJECTMANAGER_H
