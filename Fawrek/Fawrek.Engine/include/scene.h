#include "api.h"

#ifndef SCENE_H
#define	SCENE_H

#include "list"
#include "map"
#include "vector"

#include "utils.h"
#include "tinyxml2.h"
#include "model.h"

class FAWREK_API Scene
{
public:
	Scene();
	~Scene();

	void Load(const std::string& _sFilename);
	void Display();

	ObjectManager* m_pObjectManager;
};
#endif//SCENE_H