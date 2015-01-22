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
	Matrix m_boneOffset;
	Matrix m_finalTransformation;        

	BoneInfo()
	{
		m_boneOffset.SetZero();
		m_finalTransformation.SetZero();            
	}
};

struct VertexBoneData
{        
	uint m_uiIDs[NUM_BONES_PER_VERTEX];
	float m_fWeights[NUM_BONES_PER_VERTEX];

	VertexBoneData()
	{
		Reset();
	};
        
	void Reset()
	{
		ZERO_MEM(m_uiIDs);
		ZERO_MEM(m_fWeights);        
	}
        
	void AddBoneData(uint _uiBoneID, float _fWeight);
};

struct NodePack
{
    int m_iId;
    string m_sName;
    int m_iNbNode;
    vector<string> m_pack;

    NodePack(int _id,string _name, int _nbNode)
    {
        m_iId = _id;
        m_sName = _name;
        m_iNbNode = _nbNode;
    }

    void AddBoneToPack(const char *_nodeId)
    {
        m_pack.push_back(_nodeId);
    }
};

class Mesh;

class Skeleton
{
public :

	Skeleton(Mesh* _pMesh);
	~Skeleton();

	uint NumBones() const
    {
        return m_uiNumBones;
    }
    
	void LoadBones(uint _uiMeshIndex, const aiMesh* _paiMesh, vector<VertexBoneData>& _bones);
	uint m_uiNumBones;
	map<string,uint> m_boneMapping; // maps a bone name to its index
    vector<BoneInfo> m_boneInfo;
private:
	Mesh* m_pMesh;

};

#endif // SKELETON_H