#include "mesh.h"
#include "glew.h"
#include "assert.h"

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
	//FreeMesh(pMesh);
	Clear();
}

 
int Mesh::mmReadCh (FILE **_file)
{
	return fgetc(*_file);
}
 
void Mesh::mmSkipLine (FILE **_file)
{
	fgets(buffer, 128, *_file);
}
 
// mmReadNextParam: reads the next parameter from a *.m file stream,
// skips all unneeded characters
float Mesh::mmReadNextParam (FILE **_file)
{
	int ch = 0;
	float f = 0;
	bool legal = false;
 
	while (true)
	{
		ch = mmReadCh(_file);
		
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
			if (fseek(*_file, (ftell(*_file)- 1), SEEK_SET) != 0)
				printf("mmReadNextParam: fseek failed, sorry; check your *.m model file syntax");
 
			// read the floating-point parameter and return it
			fscanf(*_file, "%f", &f);
			return f;
		}
	}
 
	return 0; // EOF or error at this point
}

// LoadModel(); loads an m file format model into model_t *model
void Mesh::LoadMeshA (char *_sFilename)
{
	FILE *file = fopen(_sFilename, "r");
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
			vertices[i].normal.x = 0.0f;
			vertices[i].normal.y = 0.0f;
			vertices[i].normal.z = 0.0f;
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
		sprintf(buffer, "LoadModelM(): Cannot open file \"%s\"", _sFilename);
		printf(buffer);
	}
}

void Mesh::FreeMesh (Mesh *_mesh)
{
	if (_mesh->vertices)
	{
		free(_mesh->vertices);
		_mesh->vertices = NULL;
	}
	if (_mesh->indices)
	{
		free(_mesh->indices);
		_mesh->indices = NULL;
	}
}

Mesh::MeshEntry::MeshEntry()
{
    VB = 0xFFFFFFFF;
    IB = 0xFFFFFFFF;
    NumIndices  = 0;
    MaterialIndex = INVALID_MATERIAL;
};

Mesh::MeshEntry::~MeshEntry()
{
    if (VB != 0xFFFFFFFF)
    {
        glDeleteBuffers(1, &VB);
    }

    if (IB != 0xFFFFFFFF)
    {
        glDeleteBuffers(1, &IB);
    }
}

void Mesh::MeshEntry::Init(const std::vector<Vertex> &_vertices,
                          const std::vector<unsigned int> &_indices)
{
    NumIndices = _indices.size();

    glGenBuffers(1, &VB);
  	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &_indices[0], GL_STATIC_DRAW);
}

void Mesh::Clear()
{
    for (unsigned int i = 0 ; i < textures.size() ; i++) {
        SAFE_DELETE(textures[i]);
    }
}

bool Mesh::LoadMesh(const std::string &_filename)
{
    // Release the previously loaded mesh (if it exists)
    Clear();
    
    bool ret = false;
    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(_filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
    
    if (pScene) {
        ret = InitFromScene(pScene, _filename);
    }
    else {
        printf("Error parsing '%s': '%s'\n", _filename.c_str(), Importer.GetErrorString());
    }

    return ret;
}

bool Mesh::InitFromScene(const aiScene *_pScene, const std::string &_filename)
{  
    entries.resize(_pScene->mNumMeshes);
    textures.resize(_pScene->mNumMaterials);

    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0 ; i < entries.size() ; i++) {
        const aiMesh* paiMesh = _pScene->mMeshes[i];
        InitMesh(i, paiMesh);
    }

    return InitMaterials(_pScene, _filename);
}

void Mesh::InitMesh(unsigned int _index, const aiMesh *_paiMesh)
{
    entries[_index].MaterialIndex = _paiMesh->mMaterialIndex;
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0 ; i < _paiMesh->mNumVertices ; i++) {
        const aiVector3D* pPos      = &(_paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(_paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = _paiMesh->HasTextureCoords(0) ? &(_paiMesh->mTextureCoords[0][i]) : &Zero3D;

        Vertex v(Vector3(pPos->x, pPos->y, pPos->z),
                 Vector2(pTexCoord->x, pTexCoord->y),
                 Vector3(pNormal->x, pNormal->y, pNormal->z));

        vertices.push_back(v);
    }

    for (unsigned int i = 0 ; i < _paiMesh->mNumFaces ; i++) {
        const aiFace& Face = _paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        indices.push_back(Face.mIndices[0]);
        indices.push_back(Face.mIndices[1]);
        indices.push_back(Face.mIndices[2]);
    }

    entries[_index].Init(vertices, indices);
}

bool Mesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
    // Extract the directory part from the file name
    std::string::size_type SlashIndex = Filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) {
        Dir = "/";
    }
    else {
        Dir = Filename.substr(0, SlashIndex);
    }

    bool ret = true;

    // Initialize the materials
    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        textures[i] = NULL;

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string FullPath = Dir + "/" + Path.data;
                textures[i] = new Texture(FullPath.c_str(),GL_TEXTURE_2D, TRUE);

                if (!textures[i]->LoadTexture()) {
                    printf("Error loading texture '%s'\n", FullPath.c_str());
                    delete textures[i];
                    textures[i] = NULL;
                    ret = false;
                }
                else {
                    printf("Loaded texture '%s'\n", FullPath.c_str());
                }
            }
        }

        // Load a white texture in case the model does not include its own texture
        if (!textures[i]) {
            textures[i] = new Texture("white.png",GL_TEXTURE_2D, TRUE);

            ret = textures[i]->LoadTexture();
        }
    }

    return ret;
}

void Mesh::Render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (unsigned int i = 0 ; i < entries.size() ; i++) {
        glBindBuffer(GL_ARRAY_BUFFER, entries[i].VB);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entries[i].IB);

        const unsigned int MaterialIndex = entries[i].MaterialIndex;

        if (MaterialIndex < textures.size() && textures[MaterialIndex]) {
            textures[MaterialIndex]->Bind(GL_TEXTURE0);
        }

        glDrawElements(GL_TRIANGLES, entries[i].NumIndices, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}