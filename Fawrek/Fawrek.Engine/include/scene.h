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

	vector<Model*> m_models;
};
#endif//SCENE_H