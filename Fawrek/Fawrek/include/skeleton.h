#ifndef SKELETON_H
#define SKELETON_H

#include "map"
#include "vector"

#include "utils.h"
#include "matrix.h"

#include "scene.h"

#define NUM_BONES_PER_VERTEX 4

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
	uint IDs[NUM_BONES_PER_VERTEX];
	float Weights[NUM_BONES_PER_VERTEX];

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

struct NodePack
{
    int id;
    string name;
    int nbNode;
    vector<string> pack;

    NodePack(int _id,string _name, int _nbNode)
    {
        id = _id;
        name = _name;
        nbNode = _nbNode;
    }

    void AddBoneToPack(const char *_nodeId)
    {
        pack.push_back(_nodeId);
    }
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