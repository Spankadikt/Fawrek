#include <assert.h>

#include "animation.h"
#include "quaternion.h"

#include "glew.h"


Animation::Animation(const aiScene *_pScene, Mesh *_pMesh, Matrix _globalInverseTransform)
{
	pScene = _pScene;
	pMesh = _pMesh;
	m_GlobalInverseTransform = _globalInverseTransform;

	currentClip = lastClip = new Clip();
	//nextClip = new Clip();

	InitCrossfade();
}

Animation::~Animation()
{
	SAFE_DELETE(currentClip);
	SAFE_DELETE(lastClip);
}

void Animation::LoadClips(const std::string &_animdata_filename)
{
    if(_animdata_filename.empty())
    {
        Clip clip(this,0,0.0f,(float)pScene->mAnimations[0]->mDuration,false);
		clips.push_back(clip);
    }
    else
    {
        tinyxml2::XMLDocument doc;
        doc.LoadFile(_animdata_filename.c_str());

	    tinyxml2::XMLElement* animElement = doc.FirstChildElement( "ANIMATION" );
	    animElement->QueryIntAttribute( "nb_clip", &nbClip );

	    tinyxml2::XMLNode* child;
	    for( child = animElement->FirstChild(); child; child = child->NextSibling() )
	    {
			int id;
			child->ToElement()->QueryIntAttribute( "id", &id );
		    float startTime;
		    child->ToElement()->QueryFloatAttribute( "start_time", &startTime );
		    float endTime;
		    child->ToElement()->QueryFloatAttribute( "end_time", &endTime );
            bool loop;
            child->ToElement()->QueryBoolAttribute( "loop", &loop );

		    Clip clip(this,id,startTime,endTime,loop);
		    clips.push_back(clip);
	    }
    }

	currentClip = &clips[0];
	lastClip = &clips[0];
}

void Animation::SetCurrentClip(Clip *_clip)
{
    currentClip = new Clip(*_clip);

}

//void Animation::SetCurrentClipAndPlay(int num)
//{
//	nCurrentClip = num;
//    GetCurrentClip()->Play();
//}

Clip& Animation::GetCurrentClip()
{
    return *currentClip;
}

//void Animation::SetNextClip(int num)
//{
//    if(nCurrentClip<0)
//        nCurrentClip = num;
//    nNextClip = num;
//}

void Animation::SetLastClip(Clip *_clip)
{
    lastClip = new Clip(*_clip);

}

void Animation::CrossfadeToNextClip(int num)
{
	if(currentClip->id != clips[num].id)
	{
		
		lastClip = new Clip(*currentClip);


		currentClip = new Clip(clips[num]);



		InitCrossfade();
	}
	GetCurrentClip().Play();
	GetLastClip().Play();
}

Clip& Animation::GetLastClip()
{
    return *lastClip;
}


uint Animation::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{    
    for (uint i = 0 ; i < pNodeAnim->mNumPositionKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
            return i;
        }
    }

    return 0;
}


uint Animation::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumRotationKeys > 0);

    for (uint i = 0 ; i < pNodeAnim->mNumRotationKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
            return i;
        }
    }

    return 0;
}


uint Animation::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumScalingKeys > 0);
    
    for (uint i = 0 ; i < pNodeAnim->mNumScalingKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
            return i;
        }
    }

    return 0;
}


void Animation::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumPositionKeys == 1) {
        Out = pNodeAnim->mPositionKeys[0].mValue;
        return;
    }
            
    uint PositionIndex = FindPosition(AnimationTime, pNodeAnim);
    uint NextPositionIndex = (PositionIndex + 1);

    float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;

    const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}


void Animation::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	// we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1) {
        Out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }
    
    uint RotationIndex = FindRotation(AnimationTime, pNodeAnim);
    uint NextRotationIndex = (RotationIndex + 1);

    float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;

    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ   = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;    
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    Out = Out.Normalize();
}


void Animation::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumScalingKeys == 1) {
        Out = pNodeAnim->mScalingKeys[0].mValue;
        return;
    }

    uint ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
    uint NextScalingIndex = (ScalingIndex + 1);

    float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;

    const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
    const aiVector3D& End   = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}

Matrix Animation::CalcInterpolations(const aiNodeAnim* pNodeAnim, bool _crossFade)
{
    Matrix result;

    // Interpolate translation and generate translation transformation matrix
    aiVector3D Translation;
    if(!_crossFade)
    {
        CalcInterpolatedPosition(Translation, GetCurrentClip().clipCurrentTime, pNodeAnim);
    }
    else
    {
        aiVector3D currentTranslation;
        aiVector3D nextTranslation;
        CalcInterpolatedPosition(currentTranslation, GetCurrentClip().clipCurrentTime, pNodeAnim);
        CalcInterpolatedPosition(nextTranslation, GetLastClip().clipCurrentTime, pNodeAnim);
        Translation = (currentTranslation * weight) + (nextTranslation * (1-weight));
    }
    result.Translate(Translation.x, Translation.y, Translation.z);
        
    // Interpolate rotation and generate rotation transformation matrix
    aiQuaternion RotationQ;
    if(!_crossFade)
    {
        CalcInterpolatedRotation(RotationQ, GetCurrentClip().clipCurrentTime, pNodeAnim); 
    }
    else
    {
        aiQuaternion currentRotationQ;
        aiQuaternion nextRotationQ;
        CalcInterpolatedRotation(currentRotationQ, GetCurrentClip().clipCurrentTime, pNodeAnim);
        CalcInterpolatedRotation(nextRotationQ, GetLastClip().clipCurrentTime, pNodeAnim);
        Quaternion res = Quaternion::Slerp(Quaternion(currentRotationQ.x,currentRotationQ.y,currentRotationQ.z,currentRotationQ.w),Quaternion(nextRotationQ.x,nextRotationQ.y,nextRotationQ.z,nextRotationQ.w),weight);
        RotationQ = aiQuaternion(res.w,res.x,res.y,res.z);
    }
	Quaternion qTest = Quaternion(RotationQ.x,RotationQ.y,RotationQ.z,RotationQ.w);
	result.Rotate(qTest);

	// Interpolate scaling and generate scaling transformation matrix
    aiVector3D Scaling;
    if(!_crossFade)
    {
        CalcInterpolatedScaling(Scaling, GetCurrentClip().clipCurrentTime, pNodeAnim);
    }
    else
    {
        aiVector3D currentScaling;
        aiVector3D nextScaling;
        CalcInterpolatedScaling(currentScaling, GetCurrentClip().clipCurrentTime, pNodeAnim);
        CalcInterpolatedScaling(nextScaling, GetLastClip().clipCurrentTime, pNodeAnim);
        Scaling = (currentScaling * weight) + (nextScaling * (1-weight));
    }
    result.Scale(Scaling.x, Scaling.y, Scaling.z);

    return result;
}

void Animation::ReadNodeHierarchy(const aiNode* pNode, const Matrix& ParentTransform, bool _crossFade)
{    
    string NodeName(pNode->mName.data);
	
    const aiAnimation* pAnimation = pScene->mAnimations[0];
        
    Matrix NodeTransformation(pNode->mTransformation);
     
    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
    
    if (pNodeAnim) {
		Matrix result;
        result = CalcInterpolations(pNodeAnim,_crossFade);

        // set the above combined transformations
        NodeTransformation = result;
    }
       
    Matrix GlobalTransformation = ParentTransform * NodeTransformation;
    
	if (pMesh->pSkeleton->m_BoneMapping.find(NodeName) != pMesh->pSkeleton->m_BoneMapping.end()) {
        uint BoneIndex = pMesh->pSkeleton->m_BoneMapping[NodeName];
        pMesh->pSkeleton->m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * pMesh->pSkeleton->m_BoneInfo[BoneIndex].BoneOffset;
    }
    
    for (uint i = 0 ; i < pNode->mNumChildren ; i++) {
        ReadNodeHierarchy(pNode->mChildren[i], GlobalTransformation, _crossFade);
    }
}

void Animation::InitCrossfade()
{
	weight = 1;
    startCrossfade = -1;
}


void Animation::BoneTransform(float TimeInSeconds, vector<Matrix>& Transforms)
{
	Matrix Identity = Matrix::Identity;
    
    if(pScene->HasAnimations() && GetCurrentClip().state == Clip::ClipState::PLAY)
	{    
        
        bool crossfade = false;
		if(GetLastClip().id != GetCurrentClip().id && GetLastClip().state == Clip::ClipState::PLAY)
        {
            if(startCrossfade < 0)
                startCrossfade = TimeInSeconds;
            crossfade = true;
            GetLastClip().SetClipCurrentTime(TimeInSeconds);
            
            float dt = TimeInSeconds - startCrossfade;
            weight -= dt / 0.8f;
            if(weight>1)
                weight = 1;
			if(weight<0)
			{
				weight = 0;
				GetLastClip().Stop();
			}
        }
		GetCurrentClip().SetClipCurrentTime(TimeInSeconds);
        ReadNodeHierarchy(pScene->mRootNode, Identity, crossfade);
	}

    Transforms.resize(pMesh->pSkeleton->m_NumBones);

    for (uint i = 0 ; i < pMesh->pSkeleton->m_NumBones ; i++) {
        Transforms[i] = pMesh->pSkeleton->m_BoneInfo[i].FinalTransformation;
    }
}


const aiNodeAnim* Animation::FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
{
    for (uint i = 0 ; i < pAnimation->mNumChannels ; i++) {
        const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
        
        if (string(pNodeAnim->mNodeName.data) == NodeName) {
            return pNodeAnim;
        }
    }
    
    return NULL;
}