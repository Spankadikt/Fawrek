#include "mesh.h"
#include "glew.h"

/*Mesh::Mesh()
{
	vertices[0] = Vertex(Vector3(-1.0f, 1.0f, -1.0f),Vector2(0.0f,1.0f));
    vertices[1] = Vertex(Vector3(1.0f, 1.0f, -1.0f),Vector2(1.0f,1.0f));
    vertices[2] = Vertex(Vector3(1.0f, 1.0f, 1.0f),Vector2(1.0f,0.0f));
    vertices[3] = Vertex(Vector3(-1.0f, 1.0f, 1.0f),Vector2(0.0f,0.0f));
	vertices[4] = Vertex(Vector3(-1.0f, -1.0f, -1.0f),Vector2(0.0f,1.0f));
    vertices[5] = Vertex(Vector3(1.0f, -1.0f, -1.0f),Vector2(1.0f,1.0f));
    vertices[6] = Vertex(Vector3(1.0f, -1.0f, 1.0f),Vector2(1.0f,0.0f));
    vertices[7] = Vertex(Vector3(-1.0f, -1.0f, 1.0f),Vector2(0.0f,0.0f));

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
                               
}*/
Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	FreeMesh(pMesh);
}

 
int Mesh::mmReadCh (FILE **file)
{
	return fgetc(*file);
}
 
void Mesh::mmSkipLine (FILE **file)
{
	fgets(buffer, 128, *file);
}
 
// mmReadNextParam: reads the next parameter from a *.m file stream,
// skips all unneeded characters
float Mesh::mmReadNextParam (FILE **file)
{
	int ch = 0;
	float f = 0;
	bool legal = false;
 
	while (true)
	{
		ch = mmReadCh(file);
		
                // EOF or error: set err to 1 and break out of the loop
		if (ch == EOF)
		{
			printf("mmReadNextParam: unexpected EOF or parsing error\r\ncheck your *.m model file syntax");
			break;
		}
 
                // skip spaces or any other misc. characters (, . etc)
                // also; a vertex param. could be negative
                // so look out for '-' (0x2d) while parsing
 
		((ch >= 0x30  && ch <= 0x39) || ch == 0x2d) ? legal = true : legal = false;
 
		if (legal)
		{
			// back up by one character
			if (fseek(*file, (ftell(*file)- 1), SEEK_SET) != 0)
				printf("mmReadNextParam: fseek failed, sorry; check your *.m model file syntax");
 
			// read the floating-point parameter and return it
			fscanf(*file, "%f", &f);
			return f;
		}
	}
 
	return 0; // EOF or error at this point
}

// LoadModel(); loads an m file format model into model_t *model
void Mesh::LoadMesh (char *sFilename)
{
	FILE *file = fopen(sFilename, "r");
	FILE *temp = file;
	if (file)
	{
		// find the "vertices" tag
		while (true)
			if (strncmp(fgets(buffer, 128, file), "vertices", 8) == 0)
				break;
 
		// read the number of vertex in this model
		sscanf(buffer, "vertices %d", &nVertices);
 
		// allocate enough memory for this model
		vertices = (Vertex*)malloc(nVertices * sizeof(Vertex));
 
		// read all vertices
		for (int i=0; i < nVertices; i++) {
			vertices[i].position.x = mmReadNextParam(&file);
			vertices[i].position.y = mmReadNextParam(&file);
			vertices[i].position.z = mmReadNextParam(&file);

			vertices[i].uv.u = mmReadNextParam(&file);
			vertices[i].uv.v = mmReadNextParam(&file);

			vertices[i].normal.x = mmReadNextParam(&file);
			vertices[i].normal.y = mmReadNextParam(&file);
			vertices[i].normal.z = mmReadNextParam(&file);
		}

		// find the "vertices" tag
		while (true)
			if (strncmp(fgets(buffer, 128, file), "indices", 7) == 0)
				break;

		// read the number of indices in this model
		sscanf(buffer, "indices %d", &nIndices);
 
		// allocate enough memory for this model
		indices = (int*)malloc(nIndices * sizeof(int));
 
		// read all indices
		for (int i=0; i < nIndices; i++) {
			indices[i] = mmReadNextParam(&file);
		}

 
		fclose(file);
	}
	else
	{
		sprintf(buffer, "LoadModelM(): Cannot open file \"%s\"", sFilename);
		printf(buffer);
	}
}

void Mesh::FreeMesh (Mesh *mesh)
{
	if (mesh->vertices)
	{
		free(mesh->vertices);
		mesh->vertices = NULL;
	}
	if (mesh->indices)
	{
		free(mesh->indices);
		mesh->indices = NULL;
	}
}