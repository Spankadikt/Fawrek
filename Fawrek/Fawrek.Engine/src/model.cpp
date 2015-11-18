#include "model.h"

Model::Model(const std::string& _sFilename)
{
	m_pScene = NULL;

	if (!ModelInit(_sFilename)) {
        printf("Model init failed\n");   
    }

	m_translation = Vector3(0.0f,0.0f,0.0f);
	m_rotation = Vector3(0.0f,0.0f,0.0f);
	m_scale = Vector3(1.0f,1.0f,1.0f);

	m_bSelected = false;
}

Model::Model(const std::string& _sFilename, int _nId, Vector3 _vTranslate, Vector3 _vRotate, Vector3 _vScale, const std::string& _sAnimdataFilename)
{
	m_pScene = NULL;

    if (!ModelInit(_sFilename,_sAnimdataFilename)) {
        printf("Model init failed\n");   
    }

	m_id = _nId;

	m_translation = _vTranslate;
	m_rotation = _vRotate;
	m_scale = _vScale;

	m_bSelected = false;
}

Model::~Model()
{
	SAFE_DELETE(m_pMesh);
}

bool Model::ModelInit(const std::string& _sFilename, const std::string& _sAnimdataFilename)
{
	m_pMesh = new Mesh();

	bool ret = false;

    m_pScene = m_importer.ReadFile(_sFilename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals );//aiProcess_FlipUVs for D3D
    
    if (m_pScene) {  
        m_globalInverseTransform = m_pScene->mRootNode->mTransformation;
        m_globalInverseTransform.GetInverse();
        ret = m_pMesh->InitFromScene(m_pScene, _sFilename);
    }
    else {
        printf("Error parsing '%s': '%s'\n", _sFilename.c_str(), m_importer.GetErrorString());
    }

	return ret;
}

void Model::Render(Camera* _pCamera, Shader* _pShader, float _fRunningTime)
{
	Matrix modelMatrix = Matrix::Identity;

	modelMatrix.Translate(m_translation);
	Quaternion qRotate = qRotate.FromEuler(m_rotation.m_fX,m_rotation.m_fY,m_rotation.m_fZ);
	modelMatrix.Rotate(qRotate);
	modelMatrix.Scale(m_scale);

	Matrix modelView = _pCamera->view * modelMatrix;
	Matrix viewProjection = _pCamera->projection * modelView;
		
	_pShader->SetWVP(viewProjection);
    _pShader->SetWorldMatrix(modelMatrix);

	PickingRoutine *pr = dynamic_cast<PickingRoutine*>(_pShader);
    if( pr )
		m_pMesh->Render(pr);
	else
		m_pMesh->Render(NULL);
}
