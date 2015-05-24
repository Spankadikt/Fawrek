#include "scene.h"

Scene::Scene()
{
	m_pObjectManager = new ObjectManager();
}

Scene::~Scene()
{
	SAFE_DELETE(m_pObjectManager);
	for(int i = 0; i<m_pObjectManager->m_objects.size(); i++)
	{
		SAFE_DELETE(m_pObjectManager->m_objects[i]);
	}
}

void Scene::Load(const std::string& _sFilename)
{
	tinyxml2::XMLDocument doc;
    doc.LoadFile(_sFilename.c_str());

	tinyxml2::XMLElement* sceneElement = doc.FirstChildElement( "MODELS" );
	tinyxml2::XMLNode* child;

	for( child = sceneElement->FirstChild(); child; child = child->NextSibling() )
	{
			int id;
			child->ToElement()->QueryIntAttribute( "id", &id );
		    const char *name = child->ToElement()->Attribute( "name" );
			std::string translation ( child->ToElement()->Attribute( "translation" ) );
			std::string rotation ( child->ToElement()->Attribute( "rotation" ) );
			std::string scale ( child->ToElement()->Attribute( "scale" ) );
			std::string filename (child->ToElement()->Attribute( "filename" ));
			std::string animationfilename (child->ToElement()->Attribute( "animationfilename" ));
            bool hide;
            child->ToElement()->QueryBoolAttribute( "hide", &hide );

			if(!translation.empty() && !rotation.empty() && !scale.empty() && !animationfilename.empty())
			{
				std::vector<std::string> splitedTranslation = split(translation, ',');
				std::vector<std::string> splitedRotation = split(rotation, ',');
				std::vector<std::string> splitedScale = split(scale, ',');

				Vector3 vTranslation(stof(splitedTranslation[0].c_str()),stof(splitedTranslation[1].c_str()),stof(splitedTranslation[2].c_str()));
				Vector3 vRotation(stof(splitedRotation[0].c_str()),stof(splitedRotation[1].c_str()),stof(splitedRotation[2].c_str()));
				Vector3 vScale(stof(splitedScale[0].c_str()),stof(splitedScale[1].c_str()),stof(splitedScale[2].c_str()));

				Model *pModel = new Model(filename,id,vTranslation,vRotation,vScale,animationfilename);
				m_pObjectManager->m_objects.push_back(pModel);
			}
			else
			{
				Model *pModel = new Model(filename);
				m_pObjectManager->m_objects.push_back(pModel);
			}
	}
}

void Scene::Display()
{
}