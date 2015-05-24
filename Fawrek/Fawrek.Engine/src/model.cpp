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
}

Model::~Model()
{
	SAFE_DELETE(m_pMesh);
    SAFE_DELETE(m_pSkeleton);
	SAFE_DELETE(m_pAnimation);
    SAFE_DELETE(m_pAnimationBis);
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

    m_pAnimation = new Animation(m_pScene,m_pMesh,m_globalInverseTransform,Animation::BodyPart::LOWER_BODY);
    m_pAnimationBis = new Animation(m_pScene,m_pMesh,m_globalInverseTransform,Animation::BodyPart::UPPER_BODY);

    if(m_pScene->HasAnimations())
    {
        m_pAnimation->LoadClips(_sAnimdataFilename);
        m_pAnimationBis->LoadClips(_sAnimdataFilename);
    }

	return ret;
}

void Model::Render(Camera* _pCamera, Shader* _pShader, float _fRunningTime)
{
	_pShader->Enable();

	vector<Matrix> Transforms;

    m_pAnimationBis->BoneTransform(_fRunningTime, Transforms);
    m_pAnimation->BoneTransform(_fRunningTime, Transforms);

        
    for (uint i = 0 ; i < Transforms.size() ; i++) {
        _pShader->SetBoneTransform(i, Transforms[i]);
    }

	Matrix modelMatrix = Matrix::Identity;

	modelMatrix.Translate(m_translation);
	Quaternion qRotate = qRotate.FromEuler(m_rotation.m_fX,m_rotation.m_fY,m_rotation.m_fZ);
	modelMatrix.Rotate(qRotate);
	modelMatrix.Scale(m_scale);

	Matrix modelView = _pCamera->view * modelMatrix;
	Matrix viewProjection = _pCamera->projection * modelView;
		
	_pShader->SetWVP(viewProjection);
    _pShader->SetWorldMatrix(modelMatrix);

	m_pMesh->Render();

	if(m_pAnimation->m_pCurrentClip->m_state == Clip::ClipState::STOP)
	{
        if(!m_pAnimation->m_pCurrentClip->m_bLoop && m_pAnimation->m_pNextClip != NULL)
		{
            m_pAnimation->CrossfadeToClip(m_pAnimation->m_pNextClip);
		}
	}
    if(m_pAnimationBis->m_pCurrentClip->m_state == Clip::ClipState::STOP)
	{
        if(!m_pAnimationBis->m_pCurrentClip->m_bLoop && m_pAnimationBis->m_pNextClip != NULL)
		{
            m_pAnimationBis->CrossfadeToClip(m_pAnimationBis->m_pNextClip);
		}
	}
}
