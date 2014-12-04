#include "mesh.h"

Mesh::Mesh()
{
	vertices[0] = Vector3(-1.0f, 1.0f, -1.0f);
    vertices[1] = Vector3(1.0f, 1.0f, -1.0f);
    vertices[2] = Vector3(1.0f, 1.0f, 1.0f);
    vertices[3] = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[4] = Vector3(-1.0f, -1.0f, -1.0f);
    vertices[5] = Vector3(1.0f, -1.0f, -1.0f);
    vertices[6] = Vector3(1.0f, -1.0f, 1.0f);
    vertices[7] = Vector3(-1.0f, -1.0f, 1.0f);

	indices[ 0] = 0;		indices[ 1] = 1;		indices[ 2] = 2;//top
	indices[ 3] = 2;		indices[ 4] = 3;		indices[ 5] = 0;

	indices[ 6] = 4;		indices[ 7] = 5;		indices[ 8] = 6;//bot
	indices[ 9] = 6;		indices[10] = 7;		indices[11] = 4;

	indices[12] = 0;		indices[13] = 4;		indices[14] = 7;//left
	indices[15] = 7;		indices[16] = 3;		indices[17] = 0;

	indices[18] = 1;		indices[19] = 5;		indices[20] = 6;//right
	indices[21] = 6;		indices[22] = 2;		indices[23] = 1;  

	indices[24] = 3;		indices[25] = 2;		indices[26] = 6;//front
	indices[27] = 6;		indices[28] = 7;		indices[29] = 3;

	indices[30] = 0;		indices[31] = 1;		indices[32] = 5;//back
	indices[33] = 5;		indices[34] = 4;		indices[35] = 0;     
                               
}

Mesh::~Mesh()
{
}