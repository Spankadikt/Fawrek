#ifndef SKELETON_H
#define SKELETON_H

#include "map"
#include "vector"

#include "utils.h"
#include "matrix.h"

#include "scene.h"

#define NUM_BONES_PER_VEREX 4

struct BoneInfo
{
	Matrix BoneOffset;
	Matrix FinalTransformation;        

	BoneInfo()
	{
		BoneOffset.SetZero();
		FinalTransformation.SetZero();            
	}
};

struct VertexBoneData
{        
	uint IDs[NUM_BONES_PER_VEREX];
	float Weights[NUM_BONES_PER_VEREX];

	VertexBoneData()
	{
		Reset();
	};
        
	void Reset()
	{
		ZERO_MEM(IDs);
		ZERO_MEM(Weights);        
	}
        
	void AddBoneData(uint BoneID, float Weight);
};

class Mesh;

class Skeleton
{
public :

	Skeleton(Mesh *_pMesh);
	~Skeleton();

	uint NumBones() const
    {
        return m_NumBones;
    }
    
	void LoadBones(uint MeshIndex, const aiMesh* paiMesh, vector<VertexBoneData>& Bones);
	uint m_NumBones;
	map<string,uint> m_BoneMapping; // maps a bone name to its index
    vector<BoneInfo> m_BoneInfo;
private:
	Mesh *pMesh;

};

#endif // SKELETON_H