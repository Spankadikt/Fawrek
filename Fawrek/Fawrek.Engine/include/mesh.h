#include "api.h"

#ifndef MESH_H
#define MESH_H

#include "map"
#include "vector"

#include "GL/glew.h"
//#include "GL/gl.h"
#include "vertex.h"
#include "texture.h"
#include "utils.h"
#include "matrix.h"
#include "skeleton.h"
#include "pickingroutine.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

class FAWREK_API Mesh
{
public:
	Mesh();
	~Mesh();

	void Init();
	void Render(PickingRoutine *_pPickingRoutine);

	bool InitFromScene(const aiScene *_pScene, const std::string &_sFilename);

    const aiScene* m_pScene;
	Skeleton* m_pSkeleton;

	#define INVALID_MATERIAL 0xFFFFFFFF

	struct MeshEntry {
        MeshEntry()
        {
            m_uiNumIndices    = 0;
            m_uiBaseVertex    = 0;
            m_uiBaseIndex     = 0;
            m_uiMaterialIndex = INVALID_MATERIAL;
        }
        
        unsigned int m_uiNumIndices;
        unsigned int m_uiBaseVertex;
        unsigned int m_uiBaseIndex;
        unsigned int m_uiMaterialIndex;
    };
	
    std::vector<MeshEntry> m_entries;
    std::vector<Texture*> m_textures;

	void Clear();
private:
    void InitMesh(uint _uiMeshIndex,
                  const aiMesh* _paiMesh,
                  vector<Vector3>& _positions,
                  vector<Vector3>& _normals,
                  vector<Vector2>& _texCoords,
                  vector<VertexBoneData>& _bones,
                  vector<unsigned int>& _indices);

    bool InitMaterials(const aiScene *_pScene, const std::string &_sFilename);

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

