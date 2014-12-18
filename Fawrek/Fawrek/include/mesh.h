#ifndef MESH_H
#define MESH_H

#include "map"
#include "vector"

#include "glew.h"
#include "vertex.h"
#include "texture.h"
#include "utils.h"

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

	Vertex *vertices;//8
	int *indices;//36
	Mesh *pMesh;

	int nVertices;
	int nIndices;

private:
	bool InitFromScene(const aiScene *_pScene, const std::string &_filename);
    void InitMesh(unsigned int _index, const aiMesh* _paiMesh);
    bool InitMaterials(const aiScene *_pScene, const std::string &_filename);
    void Clear();

	#define INVALID_MATERIAL 0xFFFFFFFF

    struct MeshEntry {
        MeshEntry();

        ~MeshEntry();

        void Init(const std::vector<Vertex> &_vertices,
                  const std::vector<unsigned int> &_indices);

        GLuint VB;
        GLuint IB;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::vector<MeshEntry> entries;
    std::vector<Texture*> textures;
};


#endif //MESH_H

