#include "api.h"

#ifndef MODEL_H
#define MODEL_H

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

class FAWREK_API Model : public Object
{
public:
	Model(const string& _filename);
	Model(const string& _filename, int _nId, Vector3 _vTranslate, Vector3 _vRotate, Vector3 _vScale, const std::string& _sAnimdataFilename = "");
	~Model();

	void Render(Camera* _camera, Shader* _shader, float _fRunningTime);

	//mesh , skeleton and anim stuff
	Assimp::Importer m_importer;
	const aiScene* m_pScene;
	Matrix m_globalInverseTransform;
    
	Mesh* m_pMesh;

	bool m_bSelected;

private:
	bool ModelInit(const string& _sFilename, const std::string& _sAnimdataFilename = "");
};

#endif //MODEL_H

