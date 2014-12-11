#ifndef MESH_H
#define MESH_H

#include "vertex.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

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
};


#endif //MESH_H

