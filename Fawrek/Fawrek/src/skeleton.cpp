#include <assert.h>

#include "mesh.h"
#include "skeleton.h"



void VertexBoneData::AddBoneData(uint BoneID, float Weight)
{
    for (uint i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_uiIDs) ; i++) {
        if (m_fWeights[i] == 0.0) {
            m_uiIDs[i]     = BoneID;
            m_fWeights[i] = Weight;
            return;
        }        
    }
    
    // should never get here - more bones than we have space for
    assert(0);

}

Skeleton::Skeleton(Mesh *_pMesh)
{
	m_pMesh = _pMesh;
    m_uiNumBones = 0;
}

Skeleton::~Skeleton()
{

}

void Skeleton::LoadBones(uint MeshIndex, const aiMesh* aipMesh, vector<VertexBoneData>& Bones)
{
    for (uint i = 0 ; i < aipMesh->mNumBones ; i++) {                
        uint BoneIndex = 0;        
        string BoneName(aipMesh->mBones[i]->mName.data);
        
        if (m_boneMapping.find(BoneName) == m_boneMapping.end()) {
            // Allocate an index for a new bone
            BoneIndex = m_uiNumBones;
            m_uiNumBones++;            
	        BoneInfo bi;			
			m_boneInfo.push_back(bi);
            m_boneInfo[BoneIndex].m_boneOffset = aipMesh->mBones[i]->mOffsetMatrix;            
            m_boneMapping[BoneName] = BoneIndex;
        }
        else {
            BoneIndex = m_boneMapping[BoneName];
        }                      
        
        for (uint j = 0 ; j < aipMesh->mBones[i]->mNumWeights ; j++) {
            uint VertexID = m_pMesh->m_entries[MeshIndex].m_uiBaseVertex + aipMesh->mBones[i]->mWeights[j].mVertexId;
            float Weight  = aipMesh->mBones[i]->mWeights[j].mWeight;                   
            Bones[VertexID].AddBoneData(BoneIndex, Weight);
        }
    }    
}
