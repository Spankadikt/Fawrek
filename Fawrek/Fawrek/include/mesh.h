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

	void LoadMesh (char *sFilename);	// loads a *.m mesh file
	void DrawMesh();
	void FreeMesh (Mesh *mesh);

	Vertex *vertices;//8
	int *indices;//36
	Mesh *pMesh;

	int nVertices;
	int nIndices;

protected:
	int mmReadCh (FILE **file);
	void mmSkipLine (FILE **file);
	float mmReadNextParam (FILE **file);
	char buffer[4096];
};


#endif //MESH_H

