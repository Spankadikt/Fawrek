#include "api.h"

#ifndef SCENE_H
#define	SCENE_H

#include "list"
#include "map"
#include "vector"

#include "utils.h"
#include "tinyxml2.h"
#include "objectmanager.h"

class FAWREK_API Scene
{
public:
	Scene();
	~Scene();

	void Load(const std::string& _sFilename);
	void LoadModels(tinyxml2::XMLElement *_pDoc);
	void LoadCharacters(tinyxml2::XMLElement *_pDoc);
	void LoadLights(tinyxml2::XMLElement *_pDoc);
	void LoadCameras(tinyxml2::XMLElement *_pDoc);

	void Display();

	ObjectManager* m_pObjectManager;
};
#endif//SCENE_H