#include <assert.h>

#include "mesh.h"
#include "skeleton.h"



void VertexBoneData::AddBoneData(uint BoneID, float Weight)
{
    for (uint i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(IDs) ; i++) {
        if (Weights[i] == 0.0) {
            IDs[i]     = BoneID;
            Weights[i] = Weight;
            return;
        }        
    }
    
    // should never get here - more bones than we have space for
    assert(0);

}

Skeleton::Skeleton(Mesh *_pMesh)
{
	pMesh = _pMesh;
    m_NumBones = 0;
}

Skeleton::~Skeleton()
{

}

void Skeleton::LoadBones(uint MeshIndex, const aiMesh* aipMesh, vector<VertexBoneData>& Bones)
{
    for (uint i = 0 ; i < aipMesh->mNumBones ; i++) {                
        uint BoneIndex = 0;        
        string BoneName(aipMesh->mBones[i]->mName.data);
        
        if (m_BoneMapping.find(BoneName) == m_BoneMapping.end()) {
            // Allocate an index for a new bone
            BoneIndex = m_NumBones;
            m_NumBones++;            
	        BoneInfo bi;			
			m_BoneInfo.push_back(bi);
            m_BoneInfo[BoneIndex].BoneOffset = aipMesh->mBones[i]->mOffsetMatrix;            
            m_BoneMapping[BoneName] = BoneIndex;
        }
        else {
            BoneIndex = m_BoneMapping[BoneName];
        }                      
        
        for (uint j = 0 ; j < aipMesh->mBones[i]->mNumWeights ; j++) {
            uint VertexID = pMesh->entries[MeshIndex].BaseVertex + aipMesh->mBones[i]->mWeights[j].mVertexId;
            float Weight  = aipMesh->mBones[i]->mWeights[j].mWeight;                   
            Bones[VertexID].AddBoneData(BoneIndex, Weight);
        }
    }    
}
