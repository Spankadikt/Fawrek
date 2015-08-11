#include "api.h"

#ifndef CHARACTER_H
#define CHARACTER_H

#include "map"
#include "vector"

#include "camera.h"
#include "lightingroutine.h"
#include "skinningroutine.h"
#include "engine.h"
#include "quaternion.h"
#include "skeleton.h"
#include "mesh.h"
#include "animation.h"

class FAWREK_API Character : public Object
{
public:
	Character(const string& _filename);
	Character(const string& _filename, int _nId, Vector3 _vTranslate, Vector3 _vRotate, Vector3 _vScale, const std::string& _sAnimdataFilename = "");
	~Character();

	void Render(Camera* _camera, Shader* _shader, float _fRunningTime);

	//mesh , skeleton and anim stuff
	Assimp::Importer m_importer;
	const aiScene* m_pScene;
	Matrix m_globalInverseTransform;
    
	Mesh* m_pMesh;
	Skeleton* m_pSkeleton;
	Animation* m_pAnimation;
    //Animation* m_pAnimationBis;

	bool m_bSelected;

private:
	bool CharacterInit(const string& _sFilename, const std::string& _sAnimdataFilename = "");
};

#endif //MODEL_H

