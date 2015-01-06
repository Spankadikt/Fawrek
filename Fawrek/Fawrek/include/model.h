#ifndef MODEL_H
#define MODEL_H

#include "map"
#include "vector"

#include "camera.h"
#include "light.h"
#include "engine.h"
#include "quaternion.h"
#include "skeleton.h"
#include "mesh.h"
#include "animation.h"

class Model
{
public:
	Model(const string &_filename);
	Model(const string &_filename, Vector3 _vTranslate, Vector3 _vRotate, Vector3 _vScale);
	~Model();

	void Render(Camera *_camera, Light *_shader, float _runningTime);

	Vector3 vScale;
	Vector3 vRotate;
	Vector3 vTranslate;

	//mesh , skeleton and anim stuff
	Assimp::Importer m_Importer;
	const aiScene* m_pScene;
	Matrix m_GlobalInverseTransform;
    
	Mesh *pMesh;
	Skeleton *pSkeleton;
	Animation *pAnimation;

private:
	bool ModelInit(const string &_filename);
};

#endif //MESH_H

