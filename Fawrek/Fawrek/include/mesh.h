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

	bool LoadMesh(const std::string &Filename);
	void Render();

	void LoadMeshA (char *_sFilename);	// loads a *.m mesh file
	void DrawMesh();
	void FreeMesh (Mesh *_mesh);

	Vertex *vertices;//8
	int *indices;//36
	Mesh *pMesh;

	int nVertices;
	int nIndices;

protected:
	int mmReadCh (FILE **_file);
	void mmSkipLine (FILE **_file);
	float mmReadNextParam (FILE **_file);
	char buffer[4096];

private:
	bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();

	#define INVALID_MATERIAL 0xFFFFFFFF

    struct MeshEntry {
        MeshEntry();

        ~MeshEntry();

        void Init(const std::vector<Vertex>& Vertices,
                  const std::vector<unsigned int>& Indices);

        GLuint VB;
        GLuint IB;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::vector<MeshEntry> entries;
    std::vector<Texture*> textures;
};


#endif //MESH_H

