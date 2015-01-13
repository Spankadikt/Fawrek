#include "model.h"

Model::Model(const std::string &_filename)
{
	m_pScene = NULL;

	if (!ModelInit(_filename)) {
        printf("Model init failed\n");   
    }

	vTranslate = Vector3(0.0f,0.0f,0.0f);
	vRotate = Vector3(0.0f,0.0f,0.0f);
	vScale = Vector3(1.0f,1.0f,1.0f);


}

Model::Model(const std::string &_filename, Vector3 _vTranslate, Vector3 _vRotate, Vector3 _vScale, const std::string &_animdata_filename)
{
	m_pScene = NULL;

    if (!ModelInit(_filename,_animdata_filename)) {
        printf("Model init failed\n");   
    }

	vTranslate = _vTranslate;
	vRotate = _vRotate;
	vScale = _vScale;

	
}

Model::~Model()
{
	SAFE_DELETE(pMesh);
	SAFE_DELETE(pAnimation);
}

bool Model::ModelInit(const std::string &_filename, const std::string &_animdata_filename)
{
	pMesh = new Mesh();

	bool ret = false;

    m_pScene = m_Importer.ReadFile(_filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals );//aiProcess_FlipUVs for D3D
    
    if (m_pScene) {  
        m_GlobalInverseTransform = m_pScene->mRootNode->mTransformation;
        m_GlobalInverseTransform.GetInverse();
        ret = pMesh->InitFromScene(m_pScene, _filename);
    }
    else {
        printf("Error parsing '%s': '%s'\n", _filename.c_str(), m_Importer.GetErrorString());
    }

	pAnimation = new Animation(m_pScene,pMesh,m_GlobalInverseTransform);
    if(m_pScene->HasAnimations())
    {
        pAnimation->LoadClips(_animdata_filename);
    }

	return ret;
}


void Model::Render(Camera *_pCamera, Light *_pLight, float _runningTime)
{
	_pLight->Enable();

	vector<Matrix> Transforms;

    pAnimation->BoneTransform(_runningTime, Transforms);
        
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

	pMesh->Render();
}

