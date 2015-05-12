#include <assert.h>

#include "animation.h"
#include "quaternion.h"

#include "GL/glew.h"


Animation::Animation(const aiScene* _pScene, Mesh* _pMesh, Matrix _globalInverseTransform, BodyPart _bodyPartAffected)
{
    m_pCurrentClip = NULL;
    m_pLastClip = NULL;
    m_pNextClip = NULL;

    bodyPartAffected = _bodyPartAffected;
	m_pScene = _pScene;
	m_pMesh = _pMesh;
	m_GlobalInverseTransform = _globalInverseTransform;

	m_pCurrentClip = m_pLastClip = new Clip();

	InitCrossfade();
}

Animation::~Animation()
{
	SAFE_DELETE(m_pCurrentClip);
	SAFE_DELETE(m_pLastClip);
    SAFE_DELETE(m_pNextClip);
	SAFE_DELETE(m_pNodePack);
}

void Animation::LoadClips(const std::string& _sFilename)
{
    if(_sFilename.empty())
    {
        Clip clip(this,0,0.0f,(float)m_pScene->mAnimations[0]->mDuration,false);
		m_clips.push_back(clip);
    }
    else
    {
        tinyxml2::XMLDocument doc;
        doc.LoadFile(_sFilename.c_str());

	    tinyxml2::XMLElement* animElement = doc.FirstChildElement( "CLIPS" );
	    animElement->QueryIntAttribute( "nb_clip", &m_iNbClip );

	    tinyxml2::XMLNode* child;
	    for( child = animElement->FirstChild(); child; child = child->NextSibling() )
	    {
            /*string bodyPart = child->ToElement()->Attribute( "body_part" );
            
            bool addClip = false;
            switch(bodyPartAffected)
            {
            case BodyPart::FULL_BODY:
                if(bodyPart == "full_body")
                    addClip = true;
                break;
            case BodyPart::LOWER_BODY:
                if(bodyPart == "lower_body")
                    addClip = true;
                break;
            case BodyPart::UPPER_BODY:
                if(bodyPart == "upper_body")
                    addClip = true;
                break;
            default:
                break;
            }

            if(addClip)
            {*/
			    int id;
			    child->ToElement()->QueryIntAttribute( "id", &id );
		        float startTime;
		        child->ToElement()->QueryFloatAttribute( "start_time", &startTime );
		        float endTime;
		        child->ToElement()->QueryFloatAttribute( "end_time", &endTime );
                bool loop;
                child->ToElement()->QueryBoolAttribute( "loop", &loop );

		        Clip clip(this,id,startTime,endTime,loop);
		        m_clips.push_back(clip);
            //}
	    }

        tinyxml2::XMLElement* skeletonElement = doc.FirstChildElement( "SKELETON" );

        tinyxml2::XMLNode* np;
        for( np = skeletonElement->FirstChild(); np; np = np->NextSibling() )
	    {

            string packName = np->ToElement()->Attribute( "name" );

            bool addNodePack = false;
            switch(bodyPartAffected)
            {
            case BodyPart::FULL_BODY:
                if(packName == "full_body")
                    addNodePack = true;
                break;
            case BodyPart::LOWER_BODY:
                if(packName == "lower_body" || packName == "common")
                    addNodePack = true;
                break;
            case BodyPart::UPPER_BODY:
                if(packName == "upper_body" || packName == "common")
                    addNodePack = true;
                break;
            default:
                break;
            }
            if(addNodePack)
            {
                int id;
                np->ToElement()->QueryIntAttribute( "id" , &id );
                int nbNode;
                np->ToElement()->QueryIntAttribute( "nb_node", &nbNode );

                m_pNodePack = new NodePack(id, packName, nbNode);

                for( child = np->FirstChild(); child; child = child->NextSibling() )
	            {
                    const char *nodeId = child->ToElement()->Attribute( "nodeId" );
                    m_pNodePack->AddBoneToPack(nodeId);
                }
            }
        }
    }

	m_pCurrentClip = &m_clips[0];
	m_pLastClip = &m_clips[0];
}

void Animation::SetCurrentClip(Clip* _pClip)
{
    m_pCurrentClip = new Clip(*_pClip);
}

Clip& Animation::GetCurrentClip()
{
    return *m_pCurrentClip;
}

void Animation::SetLastClip(Clip* _pClip)
{
    m_pLastClip = new Clip(*_pClip);
}

void Animation::CrossfadeToClip(int _iNum)
{
	if(m_pCurrentClip->m_iId != m_clips[_iNum].m_iId || !m_clips[_iNum].m_bLoop)
	{
		m_pLastClip = new Clip(*m_pCurrentClip);

        for(std::size_t i=0;i<m_clips.size();i++)
        {
            if(m_clips[i].m_iId == _iNum)
            {
                m_pCurrentClip = new Clip(m_clips[i]);
                break;
            }
        }
		
		InitCrossfade();

		GetCurrentClip().Play();
		GetLastClip().Play();
	}
	else if(m_pCurrentClip == &m_clips[0] && m_pLastClip == &m_clips[0])//first time
	{
		m_pLastClip = new Clip(*m_pCurrentClip);

		m_pCurrentClip = new Clip(m_clips[_iNum]);

		InitCrossfade();

		GetCurrentClip().Play();
		GetLastClip().Play();
	}
}

void Animation::CrossfadeToClip(Clip *_pClip)
{
	if(m_pCurrentClip->m_iId != _pClip->m_iId || !_pClip->m_bLoop)
	{
		m_pLastClip = new Clip(*m_pCurrentClip);

        for(std::size_t i=0;i<m_clips.size();i++)
        {
            if(m_clips[i].m_iId == _pClip->m_iId)
            {
		        m_pCurrentClip = new Clip(m_clips[i]);
            }
        }

		InitCrossfade();

		GetCurrentClip().Play();
		GetLastClip().Play();
	}
	else if(*m_pCurrentClip == *_pClip && *m_pLastClip == *_pClip)//first time
	{
		m_pLastClip = new Clip(*m_pCurrentClip);

		m_pCurrentClip = new Clip(*_pClip);

		InitCrossfade();

		GetCurrentClip().Play();
		GetLastClip().Play();
	}
}

Clip& Animation::GetLastClip()
{
    return *m_pLastClip;
}

void Animation::QueueNextClip(Clip* _pClip)
{
    m_pNextClip = _pClip;
}

uint Animation::FindPosition(float _fAnimationTime, const aiNodeAnim* _pNodeAnim)
{    
    assert(_pNodeAnim->mNumPositionKeys > 0);

    for (uint i = 0 ; i < _pNodeAnim->mNumPositionKeys - 1 ; i++) {
        if (_fAnimationTime < (float)_pNodeAnim->mPositionKeys[i + 1].mTime)
            return i;
    }

    return 0;
}


uint Animation::FindRotation(float _fAnimationTime, const aiNodeAnim* _pNodeAnim)
{
    assert(_pNodeAnim->mNumRotationKeys > 0);

    for (uint i = 0 ; i < _pNodeAnim->mNumRotationKeys - 1 ; i++)
    {
        if (_fAnimationTime < (float)_pNodeAnim->mRotationKeys[i + 1].mTime)
            return i;
    }

    return 0;
}


uint Animation::FindScaling(float _fAnimationTime, const aiNodeAnim* _pNodeAnim)
{
    assert(_pNodeAnim->mNumScalingKeys > 0);
    
    for (uint i = 0 ; i < _pNodeAnim->mNumScalingKeys - 1 ; i++)
    {
        if (_fAnimationTime < (float)_pNodeAnim->mScalingKeys[i + 1].mTime)
            return i;
    }

    return 0;
}


void Animation::CalcInterpolatedPosition(aiVector3D& _out, float _fAnimationTime, const aiNodeAnim* _pNodeAnim)
{
    if (_pNodeAnim->mNumPositionKeys == 1)
    {
        _out = _pNodeAnim->mPositionKeys[0].mValue;
        return;
    }
            
    uint PositionIndex = FindPosition(_fAnimationTime, _pNodeAnim);
    uint NextPositionIndex = (PositionIndex + 1);

    float DeltaTime = (float)(_pNodeAnim->mPositionKeys[NextPositionIndex].mTime - _pNodeAnim->mPositionKeys[PositionIndex].mTime);
    float Factor = (_fAnimationTime - (float)_pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;

    const aiVector3D& Start = _pNodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D& End = _pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
    aiVector3D Delta = End - Start;
    _out = Start + Factor * Delta;
}


void Animation::CalcInterpolatedRotation(aiQuaternion& _out, float _fAnimationTime, const aiNodeAnim* _pNodeAnim)
{
	// we need at least two values to interpolate...
    if (_pNodeAnim->mNumRotationKeys == 1)
    {
        _out = _pNodeAnim->mRotationKeys[0].mValue;
        return;
    }
    
    uint RotationIndex = FindRotation(_fAnimationTime, _pNodeAnim);
    uint NextRotationIndex = (RotationIndex + 1);

    float DeltaTime = (float)(_pNodeAnim->mRotationKeys[NextRotationIndex].mTime - _pNodeAnim->mRotationKeys[RotationIndex].mTime);
    float Factor = (_fAnimationTime - (float)_pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;

    const aiQuaternion& StartRotationQ = _pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ   = _pNodeAnim->mRotationKeys[NextRotationIndex].mValue;    
    aiQuaternion::Interpolate(_out, StartRotationQ, EndRotationQ, Factor);
    _out = _out.Normalize();
}


void Animation::CalcInterpolatedScaling(aiVector3D& _out, float _fAnimationTime, const aiNodeAnim* _pNodeAnim)
{
    if (_pNodeAnim->mNumScalingKeys == 1)
    {
        _out = _pNodeAnim->mScalingKeys[0].mValue;
        return;
    }

    uint ScalingIndex = FindScaling(_fAnimationTime, _pNodeAnim);
    uint NextScalingIndex = (ScalingIndex + 1);

    float DeltaTime = (float)(_pNodeAnim->mScalingKeys[NextScalingIndex].mTime - _pNodeAnim->mScalingKeys[ScalingIndex].mTime);
    float Factor = (_fAnimationTime - (float)_pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;

    const aiVector3D& Start = _pNodeAnim->mScalingKeys[ScalingIndex].mValue;
    const aiVector3D& End   = _pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
    aiVector3D Delta = End - Start;
    _out = Start + Factor * Delta;
}

Matrix Animation::CalcInterpolations(const aiNodeAnim* _pNodeAnim, bool _crossFade)
{
    Matrix result;

    // Interpolate translation and generate translation transformation matrix
    aiVector3D Translation;
    if(!_crossFade)
    {
        CalcInterpolatedPosition(Translation, GetCurrentClip().m_fClipCurrentTime, _pNodeAnim);
    }
    else
    {
        aiVector3D currentTranslation;
        aiVector3D nextTranslation;
        CalcInterpolatedPosition(currentTranslation, GetCurrentClip().m_fClipCurrentTime, _pNodeAnim);
        CalcInterpolatedPosition(nextTranslation, GetLastClip().m_fClipCurrentTime, _pNodeAnim);
        Translation = (currentTranslation * m_fWeight) + (nextTranslation * (1-m_fWeight));
    }
    result.Translate(Translation.x, Translation.y, Translation.z);
        
    // Interpolate rotation and generate rotation transformation matrix
    aiQuaternion RotationQ;
    if(!_crossFade)
    {
        CalcInterpolatedRotation(RotationQ, GetCurrentClip().m_fClipCurrentTime, _pNodeAnim); 
    }
    else
    {
        aiQuaternion currentRotationQ;
        aiQuaternion nextRotationQ;
        CalcInterpolatedRotation(currentRotationQ, GetCurrentClip().m_fClipCurrentTime, _pNodeAnim);
        CalcInterpolatedRotation(nextRotationQ, GetLastClip().m_fClipCurrentTime, _pNodeAnim);
        Quaternion res = Quaternion::Slerp(Quaternion(currentRotationQ.x,currentRotationQ.y,currentRotationQ.z,currentRotationQ.w),Quaternion(nextRotationQ.x,nextRotationQ.y,nextRotationQ.z,nextRotationQ.w),m_fWeight);
        RotationQ = aiQuaternion(res.m_fW,res.m_fX,res.m_fY,res.m_fZ);
    }
	Quaternion qTest = Quaternion(RotationQ.x,RotationQ.y,RotationQ.z,RotationQ.w);
	result.Rotate(qTest);

	// Interpolate scaling and generate scaling transformation matrix
    aiVector3D Scaling;
    if(!_crossFade)
    {
        CalcInterpolatedScaling(Scaling, GetCurrentClip().m_fClipCurrentTime, _pNodeAnim);
    }
    else
    {
        aiVector3D currentScaling;
        aiVector3D nextScaling;
        CalcInterpolatedScaling(currentScaling, GetCurrentClip().m_fClipCurrentTime, _pNodeAnim);
        CalcInterpolatedScaling(nextScaling, GetLastClip().m_fClipCurrentTime, _pNodeAnim);
        Scaling = (currentScaling * m_fWeight) + (nextScaling * (1-m_fWeight));
    }
    result.Scale(Scaling.x, Scaling.y, Scaling.z);

    return result;
}

void Animation::ReadNodeHierarchy(const aiNode* _pNode, const Matrix& _parentTransform, bool _crossFade)
{    
    Matrix GlobalTransformation = _parentTransform ;

    for(int i=0;i<m_pNodePack->m_iNbNode;i++)
	{
		if(strcmp(m_pNodePack->m_pack[i].c_str(),_pNode->mName.C_Str())==0)
		{
            string NodeName(_pNode->mName.data);
	
            const aiAnimation* pAnimation = m_pScene->mAnimations[0];
        
            Matrix NodeTransformation(_pNode->mTransformation);
     
            const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
    
            if (pNodeAnim)
                NodeTransformation = CalcInterpolations(pNodeAnim,_crossFade);
       
            GlobalTransformation *=  NodeTransformation;

	        if (m_pMesh->m_pSkeleton->m_boneMapping.find(NodeName) != m_pMesh->m_pSkeleton->m_boneMapping.end())
            {
                uint BoneIndex = m_pMesh->m_pSkeleton->m_boneMapping[NodeName];
                m_pMesh->m_pSkeleton->m_boneInfo[BoneIndex].m_finalTransformation = m_GlobalInverseTransform * GlobalTransformation * m_pMesh->m_pSkeleton->m_boneInfo[BoneIndex].m_boneOffset;
            }

            break;
    	}
	}

    for (uint i = 0 ; i < _pNode->mNumChildren ; i++) 
    {
		ReadNodeHierarchy(_pNode->mChildren[i], GlobalTransformation, _crossFade);
    }
}

void Animation::InitCrossfade()
{
	m_fWeight = 1;
    m_fStartCrossfade = -1;
}


void Animation::BoneTransform(float _fTimeInSeconds, vector<Matrix>& _transforms)
{
	Matrix Identity = Matrix::Identity;
    
    if(m_pScene->HasAnimations() && GetCurrentClip().m_state == Clip::ClipState::PLAY)
	{    
        bool crossfade = false;

		if(GetLastClip().m_iId != GetCurrentClip().m_iId && m_fWeight>0)//if crossfafe is not finished
        {
            if(m_fStartCrossfade < 0)
                m_fStartCrossfade = _fTimeInSeconds;
            crossfade = true;
            GetLastClip().SetClipCurrentTime(_fTimeInSeconds);
            
            float dt = _fTimeInSeconds - m_fStartCrossfade;
            m_fWeight -= dt / 0.8f;
            if(m_fWeight>1)
                m_fWeight = 1;
			if(m_fWeight<0)
				m_fWeight = 0;
        }

		GetCurrentClip().SetClipCurrentTime(_fTimeInSeconds);
        ReadNodeHierarchy(m_pScene->mRootNode, Identity, crossfade);
	}

    _transforms.resize(m_pMesh->m_pSkeleton->m_uiNumBones);

    for (uint i = 0 ; i < m_pMesh->m_pSkeleton->m_uiNumBones ; i++)
    {
        _transforms[i] = m_pMesh->m_pSkeleton->m_boneInfo[i].m_finalTransformation;
    }
}


const aiNodeAnim* Animation::FindNodeAnim(const aiAnimation* _pAnimation, const string _sNodeName)
{
    for (uint i = 0 ; i < _pAnimation->mNumChannels ; i++)
    {
        const aiNodeAnim* pNodeAnim = _pAnimation->mChannels[i];
        
        if (string(pNodeAnim->mNodeName.data) == _sNodeName)
            return pNodeAnim;
    }
    
    return NULL;
}