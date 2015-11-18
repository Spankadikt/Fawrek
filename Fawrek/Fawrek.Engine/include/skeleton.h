#include "api.h"

#ifndef SKELETON_H
#define SKELETON_H

#include "map"
#include "vector"

#include "utils.h"
#include "matrix.h"

#include "assimp/scene.h"

#define NUM_BONES_PER_VERTEX 4

//string is the node_id, it's name
//uint is the index of the associated animation node
typedef std::pair <string, uint> NodePair;

struct FAWREK_API BoneInfo
{
	Matrix m_boneOffset;
	Matrix m_finalTransformation;        

	BoneInfo()
	{
		m_boneOffset.SetZero();
		m_finalTransformation.SetZero();            
	}
};

struct FAWREK_API VertexBoneData
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

struct FAWREK_API NodePack
{
    int m_iId;
    string m_sName;
    int m_iNbNode;
    vector<NodePair> m_pack;

    NodePack(int _id,string _name, int _nbNode)
    {
        m_iId = _id;
        m_sName = _name;
        m_iNbNode = _nbNode;
    }

    void AddBoneToPack(const char *_nodeId, uint _iAnimNodeIndex)
    {
        m_pack.push_back(make_pair(_nodeId,_iAnimNodeIndex));
    }
};

class FAWREK_API Mesh;

class FAWREK_API Skeleton
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