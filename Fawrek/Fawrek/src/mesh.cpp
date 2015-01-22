#include "mesh.h"

#include "glew.h"
#include "assert.h"
#include "quaternion.h"

#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

Mesh::Mesh()
{
	m_VAO = 0;
    ZERO_MEM(m_Buffers);
	m_pSkeleton = new Skeleton(this);
}

Mesh::~Mesh()
{
	SAFE_DELETE(m_pSkeleton);
	Clear();
}

void Mesh::Clear()
{
    for (unsigned int i = 0 ; i < m_textures.size() ; i++) {
        SAFE_DELETE(m_textures[i]);
    }

	if (m_Buffers[0] != 0) {
        glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);
    }
       
    if (m_VAO != 0) {
        glDeleteVertexArrays(1, &m_VAO);
        m_VAO = 0;
    }
}

bool Mesh::InitFromScene(const aiScene *_pScene, const std::string &_filename)
{  
	// Release the previously loaded mesh (if it exists)
    Clear();

	// Create the VAO
    glGenVertexArrays(1, &m_VAO);   
    glBindVertexArray(m_VAO);
    
    // Create the buffers for the vertices attributes
    glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);

	m_pScene = _pScene;

    m_entries.resize(m_pScene->mNumMeshes);
    m_textures.resize(m_pScene->mNumMaterials);

	vector<Vector3> Positions;
    vector<Vector3> Normals;
    vector<Vector2> TexCoords;
    vector<VertexBoneData> Bones;
    vector<uint> Indices;
       
    uint NumVertices = 0;
    uint NumIndices = 0;
    
    // Count the number of vertices and indices
    for (uint i = 0 ; i < m_entries.size() ; i++) {
        m_entries[i].m_uiMaterialIndex = m_pScene->mMeshes[i]->mMaterialIndex;        
        m_entries[i].m_uiNumIndices    = m_pScene->mMeshes[i]->mNumFaces * 3;
        m_entries[i].m_uiBaseVertex    = NumVertices;
        m_entries[i].m_uiBaseIndex     = NumIndices;
        
        NumVertices += m_pScene->mMeshes[i]->mNumVertices;
        NumIndices  += m_entries[i].m_uiNumIndices;
    }
    
    // Reserve space in the vectors for the vertex attributes and indices
    Positions.reserve(NumVertices);
    Normals.reserve(NumVertices);
    TexCoords.reserve(NumVertices);
    Bones.resize(NumVertices);
    Indices.reserve(NumIndices);

    // Initialize the meshes in the scene one by one
    for (uint i = 0 ; i < m_entries.size() ; i++) {
        const aiMesh* paiMesh = m_pScene->mMeshes[i];
        InitMesh(i, paiMesh, Positions, Normals, TexCoords, Bones, Indices);
    }

    if (!InitMaterials(m_pScene, _filename)) {
        return false;
    }

	// Generate and populate the buffers with vertex attributes and the indices
  	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);    

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(TEX_COORD_LOCATION);
    glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

   	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMAL_LOCATION);
    glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

   	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BONE_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(BONE_ID_LOCATION);
    glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
    glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);    
    glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)16);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);	

    return GLCheckError();
}

void Mesh::InitMesh(uint MeshIndex,
                    const aiMesh* paiMesh,
                    vector<Vector3>& Positions,
                    vector<Vector3>& Normals,
                    vector<Vector2>& TexCoords,
                    vector<VertexBoneData>& Bones,
                    vector<uint>& Indices)
{    
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    
    // Populate the vertex attribute vectors
    for (uint i = 0 ; i < paiMesh->mNumVertices ; i++) {
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

        Positions.push_back(Vector3(pPos->x, pPos->y, pPos->z));
        Normals.push_back(Vector3(pNormal->x, pNormal->y, pNormal->z));
        TexCoords.push_back(Vector2(pTexCoord->x, pTexCoord->y));        
    }

	if(paiMesh->HasBones())
	{
		m_pSkeleton->LoadBones(MeshIndex, paiMesh, Bones);
	}
    
    // Populate the index buffer
    for (uint i = 0 ; i < paiMesh->mNumFaces ; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        Indices.push_back(Face.mIndices[0]);
        Indices.push_back(Face.mIndices[1]);
        Indices.push_back(Face.mIndices[2]);
    }
}

bool Mesh::InitMaterials(const aiScene* pScene, const string& Filename)
{
    // Extract the directory part from the file name
    string::size_type slashIndex = Filename.find_last_of("/");
    string sDir;

    if (slashIndex == string::npos) {
        sDir = ".";
    }
    else if (slashIndex == 0) {
        sDir = "/";
    }
    else {
        sDir = Filename.substr(0, slashIndex);
    }

    bool bRet = true;

    // Initialize the materials
    for (uint i = 0 ; i < m_pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = m_pScene->mMaterials[i];

        m_textures[i] = NULL;

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                string p(Path.data);
                
                if (p.substr(0, 2) == ".\\") {                    
                    p = p.substr(2, p.size() - 2);
                }
				//hack for absolute texture path...
				string::size_type SlashIndex = p.find_last_of("/");
				SlashIndex++;
				p = p.substr(SlashIndex, p.size()-SlashIndex);
				//end hack
                string FullPath = sDir + "/" + p;
                    
                m_textures[i] = new Texture(FullPath.c_str(),GL_TEXTURE_2D);

                if (!m_textures[i]->LoadTexture()) {
                    printf("Error loading texture '%s'\n", FullPath.c_str());
                    delete m_textures[i];
                    m_textures[i] = NULL;
                    bRet = false;
                }
                else {
                    printf("%d - loaded texture '%s'\n", i, FullPath.c_str());
                }
            }
        }
    }

    return bRet;
}


void Mesh::Render()
{
    glBindVertexArray(m_VAO);
    
    for (uint i = 0 ; i < m_entries.size() ; i++) {
        const uint uiMaterialIndex = m_entries[i].m_uiMaterialIndex;

        assert(uiMaterialIndex < m_textures.size());
        
        if (m_textures[uiMaterialIndex]) {
            m_textures[uiMaterialIndex]->Bind(GL_TEXTURE0);
        }

		glDrawElementsBaseVertex(GL_TRIANGLES, 
                                 m_entries[i].m_uiNumIndices, 
                                 GL_UNSIGNED_INT, 
                                 (void*)(sizeof(uint) * m_entries[i].m_uiBaseIndex), 
                                 m_entries[i].m_uiBaseVertex);
    }

    // Make sure the VAO is not changed from the outside    
    glBindVertexArray(0);
}