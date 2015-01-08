#ifndef MESH_H
#define MESH_H

#include "map"
#include "vector"


#include "glew.h"
#include "vertex.h"
#include "texture.h"
#include "utils.h"
#include "matrix.h"
#include "skeleton.h"

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

	void Init();
	void Render();

	bool InitFromScene(const aiScene *_pScene, const std::string &_filename);

    const aiScene* m_pScene;
	Skeleton *pSkeleton;

	#define INVALID_MATERIAL 0xFFFFFFFF

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

	void Clear();
private:

    void InitMesh(uint MeshIndex,
                  const aiMesh* paiMesh,
                  vector<Vector3>& Positions,
                  vector<Vector3>& Normals,
                  vector<Vector2>& TexCoords,
                  vector<VertexBoneData>& Bones,
                  vector<unsigned int>& Indices);

    bool InitMaterials(const aiScene *_pScene, const std::string &_filename);

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
};


#endif //MESH_H

