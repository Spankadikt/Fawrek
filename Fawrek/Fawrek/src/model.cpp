#include "model.h"

Model::Model(const std::string &_filename)
{
	if (!mesh.LoadMesh(_filename)) {
        printf("Mesh load failed\n");   
    }

	vTranslate = Vector3(0.0f,0.0f,0.0f);
	vRotate = Vector3(0.0f,0.0f,0.0f);
	vScale = Vector3(1.0f,1.0f,1.0f);
}

Model::Model(const std::string &_filename, Vector3 _vTranslate, Vector3 _vRotate, Vector3 _vScale)
{
	if (!mesh.LoadMesh(_filename)) {
        printf("Mesh load failed\n");   
    }

	vTranslate = _vTranslate;
	vRotate = _vRotate;
	vScale = _vScale;
}

Model::~Model()
{

}

void Model::Render(Camera *_pCamera, Light *_pLight, float _runningTime)
{
	_pLight->Enable();

	vector<Matrix> Transforms;

    mesh.BoneTransform(_runningTime, Transforms);
        
    for (uint i = 0 ; i < Transforms.size() ; i++) {
        _pLight->SetBoneTransform(i, Transforms[i]);
    }

	Matrix modelMatrix = Matrix::Identity;

	modelMatrix.Translate(vTranslate);
	Quaternion qRotate = qRotate.FromEuler(vRotate.x,vRotate.y,vRotate.z);
	modelMatrix.Rotate(qRotate);
	modelMatrix.Scale(vScale);

	Matrix modelView = _pCamera->view * modelMatrix;
	Matrix viewProjection = _pCamera->projection * modelView;
		
	_pLight->SetWVP(viewProjection);
    _pLight->SetWorldMatrix(modelMatrix);

	mesh.Render();
}

