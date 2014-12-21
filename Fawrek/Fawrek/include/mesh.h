#ifndef MESH_H
#define MESH_H

#include "map"
#include "vector"

#include "glew.h"
#include "vertex.h"
#include "texture.h"
#include "utils.h"
#include "matrix.h"

#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool LoadMesh(const std::string &_filename);
	void Render();

	/*Vertex *vertices;//8
	int *indices;//36
	Mesh *pMesh;

	int nVertices;
	int nIndices;*/

	uint NumBones() const
    {
        return m_NumBones;
    }
    
    void BoneTransform(float TimeInSeconds, vector<Matrix>& Transforms);

private:

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

    void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);    
    uint FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
    uint FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
    uint FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
    const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
    void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix& ParentTransform);

	bool InitFromScene(const aiScene *_pScene, const std::string &_filename);
    void InitMesh(uint MeshIndex,
                  const aiMesh* paiMesh,
                  vector<Vector3>& Positions,
                  vector<Vector3>& Normals,
                  vector<Vector2>& TexCoords,
                  vector<VertexBoneData>& Bones,
                  vector<unsigned int>& Indices);
    void LoadBones(uint MeshIndex, const aiMesh* paiMesh, vector<VertexBoneData>& Bones);
    bool InitMaterials(const aiScene *_pScene, const std::string &_filename);
    void Clear();

	#define INVALID_MATERIAL 0xFFFFFFFF

    enum VB_TYPES {
		INDEX_BUFFER,
		POS_VB,
		NORMAL_VB,
		TEXCOORD_VB,
		BONE_VB,
		NUM_VBs            
	};

    GLuint m_VAO;
    GLuint m_Buffers[NUM_VBs];

    struct MeshEntry {
        MeshEntry()
        {
            NumIndices    = 0;
            BaseVertex    = 0;
            BaseIndex     = 0;
            MaterialIndex = INVALID_MATERIAL;
        }
        
        unsigned int NumIndices;
        unsigned int BaseVertex;
        unsigned int BaseIndex;
        unsigned int MaterialIndex;
    };

    std::vector<MeshEntry> entries;
    std::vector<Texture*> textures;

	map<string,uint> m_BoneMapping; // maps a bone name to its index
    uint m_NumBones;
    vector<BoneInfo> m_BoneInfo;
    Matrix m_GlobalInverseTransform;
    
    const aiScene* m_pScene;
    Assimp::Importer m_Importer;
};


#endif //MESH_H

