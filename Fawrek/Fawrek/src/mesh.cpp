#include "mesh.h"
#include "glew.h"
#include "assert.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	Clear();
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

bool Mesh::InitMaterials(const aiScene *_pScene, const std::string &_filename)
{
    // Extract the directory part from the file name
    std::string::size_type SlashIndex = _filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) {
        Dir = "/";
    }
    else {
        Dir = _filename.substr(0, SlashIndex);
    }

    bool ret = true;

    // Initialize the materials
    for (unsigned int i = 0 ; i < _pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = _pScene->mMaterials[i];

        textures[i] = NULL;

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string FullPath = Dir + "/" + Path.data;
                textures[i] = new Texture(FullPath.c_str(),GL_TEXTURE_2D);

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
            textures[i] = new Texture("white.png",GL_TEXTURE_2D);

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