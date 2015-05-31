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

	tinyxml2::XMLElement* pSceneLights = doc.FirstChildElement( "OBJECTS" )->FirstChildElement( "LIGHTS" );
	if(pSceneLights)
		LoadLights(pSceneLights);

	tinyxml2::XMLElement* pSceneModels = doc.FirstChildElement( "OBJECTS" )->FirstChildElement( "MODELS" );
	if(pSceneModels)
		LoadModels(pSceneModels);

	tinyxml2::XMLElement* pSceneCameras = doc.FirstChildElement( "OBJECTS" )->FirstChildElement( "CAMERAS" );
	if(pSceneCameras)
		LoadCameras(pSceneCameras);
}

void Scene::LoadModels(tinyxml2::XMLElement *_pSceneElement)
{
	tinyxml2::XMLNode* child;
	for( child = _pSceneElement->FirstChild(); child; child = child->NextSibling() )
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
		if(!translation.empty() && !rotation.empty() && !scale.empty())
		{
			std::vector<std::string> splitedTranslation = split(translation, ',');
			std::vector<std::string> splitedRotation = split(rotation, ',');
			std::vector<std::string> splitedScale = split(scale, ',');

			Vector3 vTranslation(stof(splitedTranslation[0].c_str()),stof(splitedTranslation[1].c_str()),stof(splitedTranslation[2].c_str()));
			Vector3 vRotation(stof(splitedRotation[0].c_str()),stof(splitedRotation[1].c_str()),stof(splitedRotation[2].c_str()));
			Vector3 vScale(stof(splitedScale[0].c_str()),stof(splitedScale[1].c_str()),stof(splitedScale[2].c_str()));

			Model *pModel;
			if(!animationfilename.empty())
				pModel = new Model(filename,id,vTranslation,vRotation,vScale,animationfilename);
			else
				pModel = new Model(filename,id,vTranslation,vRotation,vScale);

			m_pObjectManager->m_objects.push_back(pModel);
		}
		else
		{
			Model *pModel = new Model(filename);
			m_pObjectManager->m_objects.push_back(pModel);
		}
	}
}

void Scene::LoadLights(tinyxml2::XMLElement *_pSceneElement)
{
	tinyxml2::XMLNode* child;
	for( child = _pSceneElement->FirstChild(); child; child = child->NextSibling() )
	{
		if(strcmp(child->ToElement()->Name(),"LIGHT_DIRECTIONAL") == 0)
		{
			int id;
			child->ToElement()->QueryIntAttribute( "id", &id );
			const char *name = child->ToElement()->Attribute( "name" );
			std::string direction ( child->ToElement()->Attribute( "direction" ) );
			std::string color ( child->ToElement()->Attribute( "color" ) );
			float ambiantIntensity;
			child->ToElement()->QueryFloatAttribute( "ambiantintensity", &ambiantIntensity );
			float diffuseIntensity;
			child->ToElement()->QueryFloatAttribute( "diffuseintensity", &diffuseIntensity );

			std::vector<std::string> splitedDirection = split(direction, ',');
			std::vector<std::string> splitedColor = split(color, ',');

			Vector3 vDirection(stof(splitedDirection[0].c_str()),stof(splitedDirection[1].c_str()),stof(splitedDirection[2].c_str()));
			Vector3 vColor(stof(splitedColor[0].c_str()),stof(splitedColor[1].c_str()),stof(splitedColor[2].c_str()));

			DirectionalLight *pDirectionalLight = new DirectionalLight();
			pDirectionalLight->m_color = vColor;
			pDirectionalLight->m_fAmbientIntensity = ambiantIntensity;
			pDirectionalLight->m_fDiffuseIntensity = diffuseIntensity;
			pDirectionalLight->m_direction = vDirection;
			m_pObjectManager->m_objects.push_back(pDirectionalLight);
			
		}
	}
}
void Scene::LoadCameras(tinyxml2::XMLElement *_pSceneElement)
{
	tinyxml2::XMLNode* child;
	for( child = _pSceneElement->FirstChild(); child; child = child->NextSibling() )
	{
			int id;
			child->ToElement()->QueryIntAttribute( "id", &id );
			const char *name = child->ToElement()->Attribute( "name" );
			std::string position ( child->ToElement()->Attribute( "position" ) );
			std::string target ( child->ToElement()->Attribute( "target" ) );
			std::string up ( child->ToElement()->Attribute( "up" ) );
			float fov;
			child->ToElement()->QueryFloatAttribute( "fov", &fov );
			float nearZ;
			child->ToElement()->QueryFloatAttribute( "nearz", &nearZ );
			float farZ;
			child->ToElement()->QueryFloatAttribute( "farz", &farZ );
			int aspectRatioWidth;
			child->ToElement()->QueryIntAttribute( "aspectratiowidth", &aspectRatioWidth );
			int aspectRatioHeight;
			child->ToElement()->QueryIntAttribute( "aspectratioheight", &aspectRatioHeight );

			std::vector<std::string> splitedPosition = split(position, ',');
			std::vector<std::string> splitedTarget = split(target, ',');
			std::vector<std::string> splitedUp = split(up, ',');

			Vector3 vPosition(stof(splitedPosition[0].c_str()),stof(splitedPosition[1].c_str()),stof(splitedPosition[2].c_str()));
			Vector3 vTarget(stof(splitedTarget[0].c_str()),stof(splitedTarget[1].c_str()),stof(splitedTarget[2].c_str()));
			Vector3 vUp(stof(splitedUp[0].c_str()),stof(splitedUp[1].c_str()),stof(splitedUp[2].c_str()));

			Camera *pCamera = new Camera(vPosition,vTarget,vUp);
			pCamera->PerspectiveFOV(fov,aspectRatioWidth/aspectRatioHeight,nearZ,farZ);
			pCamera->LookAt(pCamera->pos,pCamera->target,pCamera->up);

			m_pObjectManager->m_objects.push_back(pCamera);

	}
}

void Scene::Display()
{
}