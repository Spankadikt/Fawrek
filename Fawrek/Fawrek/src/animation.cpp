#include <assert.h>

#include "animation.h"
#include "quaternion.h"

#include "glew.h"


Animation::Animation(const aiScene *_pScene, Mesh *_pMesh, Matrix _globalInverseTransform, float _animationSpeed)
{
	pScene = _pScene;
	pMesh = _pMesh;
	m_GlobalInverseTransform = _globalInverseTransform;
	animationSpeed = _animationSpeed;

    LoadClips();
	SetClipToPlay(0);
}

Animation::~Animation()
{

}

void Animation::LoadClips()
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("resources/animation_ninja.xml");

	tinyxml2::XMLElement* animElement = doc.FirstChildElement( "ANIMATION" );
	animElement->QueryIntAttribute( "nb_clip", &nbClip );

	tinyxml2::XMLNode* child;
	for( child = animElement->FirstChild(); child; child = child->NextSibling() )
	{
		//tinyxml2::XMLElement* clipElement = doc.FirstChildElement()->FirstChildElement( "CLIP" );
		float startTime;
		child->ToElement()->QueryFloatAttribute( "start_time", &startTime );
		float endTime;
		child->ToElement()->QueryFloatAttribute( "end_time", &endTime );

		Clip clip(startTime,endTime);
		clips.push_back(clip);
	}
}

void Animation::SetClipToPlay(uint num)
{
	numClipToPlay = num;
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


void Animation::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix& ParentTransform)
{    
    string NodeName(pNode->mName.data);
	
    const aiAnimation* pAnimation = pScene->mAnimations[0];
        
    Matrix NodeTransformation(pNode->mTransformation);
     
    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
    
    if (pNodeAnim) {
		Matrix result;


        // Interpolate translation and generate translation transformation matrix
        aiVector3D Translation;
        CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
        Matrix TranslationM;
        result.Translate(Translation.x, Translation.y, Translation.z);
        
        // Interpolate rotation and generate rotation transformation matrix
        aiQuaternion RotationQ;
        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim); 
		Quaternion qTest = Quaternion(RotationQ.x,RotationQ.y,RotationQ.z,RotationQ.w);
		result.Rotate(qTest);

		
		// Interpolate scaling and generate scaling transformation matrix
        aiVector3D Scaling;
        CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
        Matrix ScalingM;
        result.Scale(Scaling.x, Scaling.y, Scaling.z);
        
        
        // set the above combined transformations
        NodeTransformation = result;
    }
       
    Matrix GlobalTransformation = ParentTransform * NodeTransformation;
    
	if (pMesh->pSkeleton->m_BoneMapping.find(NodeName) != pMesh->pSkeleton->m_BoneMapping.end()) {
        uint BoneIndex = pMesh->pSkeleton->m_BoneMapping[NodeName];
        pMesh->pSkeleton->m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * pMesh->pSkeleton->m_BoneInfo[BoneIndex].BoneOffset;
    }
    
    for (uint i = 0 ; i < pNode->mNumChildren ; i++) {
        ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
    }
}

void Animation::BoneTransform(float TimeInSeconds, vector<Matrix>& Transforms)
{
	Matrix Identity = Matrix::Identity;
    
	if(pScene->HasAnimations())
	{
		float TicksPerSecond = (float)(pScene->mAnimations[0]->mTicksPerSecond != 0 ? pScene->mAnimations[0]->mTicksPerSecond : 25.0f);
		TicksPerSecond = TicksPerSecond * animationSpeed;
		float TimeInTicks = TimeInSeconds * TicksPerSecond;
		//float AnimationTime = fmod(TimeInTicks, (float)pScene->mAnimations[0]->mDuration);
        float AnimationTime = fmod(TimeInTicks, clips[numClipToPlay].GetClipLength());
        AnimationTime = clips[numClipToPlay].startTime + AnimationTime;

		ReadNodeHeirarchy(AnimationTime, pScene->mRootNode, Identity);
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