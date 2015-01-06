#include "mesh.h"

#include "glew.h"
#include "assert.h"
#include "quaternion.h"

#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

//void Mesh::VertexBoneData::AddBoneData(uint BoneID, float Weight)
//{
//    for (uint i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(IDs) ; i++) {
//        if (Weights[i] == 0.0) {
//            IDs[i]     = BoneID;
//            Weights[i] = Weight;
//            return;
//        }        
//    }
//    
//    // should never get here - more bones than we have space for
//    assert(0);
//
//}
Mesh::Mesh(const aiScene *_pScene)
{
	m_VAO = 0;
    ZERO_MEM(m_Buffers);
    //m_NumBones = 0;
	m_pScene = _pScene;

	//pSkeleton = new Skeleton();
	//pAnimation = new Animation(this);
	this->Init();
}

Mesh::~Mesh()
{
	Clear();
}

void Mesh::Clear()
{
    for (unsigned int i = 0 ; i < textures.size() ; i++) {
        SAFE_DELETE(textures[i]);
    }

	if (m_Buffers[0] != 0) {
        glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);
    }
       
    if (m_VAO != 0) {
        glDeleteVertexArrays(1, &m_VAO);
        m_VAO = 0;
    }
}

void Mesh::Init()
{
    // Release the previously loaded mesh (if it exists)
    Clear();

	// Create the VAO
    glGenVertexArrays(1, &m_VAO);   
    glBindVertexArray(m_VAO);
    
    // Create the buffers for the vertices attributes
    glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);
    
    //bool ret = false;

    //m_pScene = m_Importer.ReadFile(_filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals );//aiProcess_FlipUVs for D3D
    //
    //if (m_pScene) {  
    //    m_GlobalInverseTransform = m_pScene->mRootNode->mTransformation;
    //    m_GlobalInverseTransform.GetInverse();
    //    ret = InitFromScene(m_pScene, _filename);
    //}
    //else {
    //    printf("Error parsing '%s': '%s'\n", _filename.c_str(), m_Importer.GetErrorString());
    //}

    // Make sure the VAO is not changed from the outside
    glBindVertexArray(0);	
}

bool Mesh::InitFromScene(const aiScene *_pScene, const std::string &_filename)
{  
    entries.resize(_pScene->mNumMeshes);
    textures.resize(_pScene->mNumMaterials);

	vector<Vector3> Positions;
    vector<Vector3> Normals;
    vector<Vector2> TexCoords;
    vector<VertexBoneData> Bones;
    vector<uint> Indices;
       
    uint NumVertices = 0;
    uint NumIndices = 0;
    
    // Count the number of vertices and indices
    for (uint i = 0 ; i < entries.size() ; i++) {
        entries[i].MaterialIndex = _pScene->mMeshes[i]->mMaterialIndex;        
        entries[i].NumIndices    = _pScene->mMeshes[i]->mNumFaces * 3;
        entries[i].BaseVertex    = NumVertices;
        entries[i].BaseIndex     = NumIndices;
        
        NumVertices += _pScene->mMeshes[i]->mNumVertices;
        NumIndices  += entries[i].NumIndices;
    }
    
    // Reserve space in the vectors for the vertex attributes and indices
    Positions.reserve(NumVertices);
    Normals.reserve(NumVertices);
    TexCoords.reserve(NumVertices);
    Bones.resize(NumVertices);
    Indices.reserve(NumIndices);

    // Initialize the meshes in the scene one by one
    for (uint i = 0 ; i < entries.size() ; i++) {
        const aiMesh* paiMesh = _pScene->mMeshes[i];
        InitMesh(i, paiMesh, Positions, Normals, TexCoords, Bones, Indices);
    }

    if (!InitMaterials(_pScene, _filename)) {
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
		pSkeleton = new Skeleton(this);
		pSkeleton->LoadBones(MeshIndex, paiMesh, Bones);
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

//void Mesh::LoadBones(uint MeshIndex, const aiMesh* pMesh, vector<VertexBoneData>& Bones)
//{
//    for (uint i = 0 ; i < pMesh->mNumBones ; i++) {                
//        uint BoneIndex = 0;        
//        string BoneName(pMesh->mBones[i]->mName.data);
//        
//        if (m_BoneMapping.find(BoneName) == m_BoneMapping.end()) {
//            // Allocate an index for a new bone
//            BoneIndex = m_NumBones;
//            m_NumBones++;            
//	        BoneInfo bi;			
//			m_BoneInfo.push_back(bi);
//            m_BoneInfo[BoneIndex].BoneOffset = pMesh->mBones[i]->mOffsetMatrix;            
//            m_BoneMapping[BoneName] = BoneIndex;
//        }
//        else {
//            BoneIndex = m_BoneMapping[BoneName];
//        }                      
//        
//        for (uint j = 0 ; j < pMesh->mBones[i]->mNumWeights ; j++) {
//            uint VertexID = entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
//            float Weight  = pMesh->mBones[i]->mWeights[j].mWeight;                   
//            Bones[VertexID].AddBoneData(BoneIndex, Weight);
//        }
//    }    
//}

bool Mesh::InitMaterials(const aiScene* pScene, const string& Filename)
{
    // Extract the directory part from the file name
    string::size_type SlashIndex = Filename.find_last_of("/");
    string Dir;

    if (SlashIndex == string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) {
        Dir = "/";
    }
    else {
        Dir = Filename.substr(0, SlashIndex);
    }

    bool Ret = true;

    // Initialize the materials
    for (uint i = 0 ; i < pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        textures[i] = NULL;

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
                string FullPath = Dir + "/" + p;
                    
                textures[i] = new Texture(FullPath.c_str(),GL_TEXTURE_2D);

                if (!textures[i]->LoadTexture()) {
                    printf("Error loading texture '%s'\n", FullPath.c_str());
                    delete textures[i];
                    textures[i] = NULL;
                    Ret = false;
                }
                else {
                    printf("%d - loaded texture '%s'\n", i, FullPath.c_str());
                }
            }
        }
    }

    return Ret;
}


void Mesh::Render()
{
    glBindVertexArray(m_VAO);
    
    for (uint i = 0 ; i < entries.size() ; i++) {
        const uint MaterialIndex = entries[i].MaterialIndex;

        assert(MaterialIndex < textures.size());
        
        if (textures[MaterialIndex]) {
            textures[MaterialIndex]->Bind(GL_TEXTURE0);
        }

		glDrawElementsBaseVertex(GL_TRIANGLES, 
                                 entries[i].NumIndices, 
                                 GL_UNSIGNED_INT, 
                                 (void*)(sizeof(uint) * entries[i].BaseIndex), 
                                 entries[i].BaseVertex);
    }

    // Make sure the VAO is not changed from the outside    
    glBindVertexArray(0);
}


//uint Mesh::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
//{    
//    for (uint i = 0 ; i < pNodeAnim->mNumPositionKeys - 1 ; i++) {
//        if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
//            return i;
//        }
//    }
//
//    return 0;
//}
//
//
//uint Mesh::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//    assert(pNodeAnim->mNumRotationKeys > 0);
//
//    for (uint i = 0 ; i < pNodeAnim->mNumRotationKeys - 1 ; i++) {
//        if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
//            return i;
//        }
//    }
//
//    return 0;
//}
//
//
//uint Mesh::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//    assert(pNodeAnim->mNumScalingKeys > 0);
//    
//    for (uint i = 0 ; i < pNodeAnim->mNumScalingKeys - 1 ; i++) {
//        if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
//            return i;
//        }
//    }
//
//    return 0;
//}
//
//
//void Mesh::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//    if (pNodeAnim->mNumPositionKeys == 1) {
//        Out = pNodeAnim->mPositionKeys[0].mValue;
//        return;
//    }
//            
//    uint PositionIndex = FindPosition(AnimationTime, pNodeAnim);
//    uint NextPositionIndex = (PositionIndex + 1);
//
//    float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
//    float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
//
//    const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
//    const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
//    aiVector3D Delta = End - Start;
//    Out = Start + Factor * Delta;
//}
//
//
//void Mesh::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//	// we need at least two values to interpolate...
//    if (pNodeAnim->mNumRotationKeys == 1) {
//        Out = pNodeAnim->mRotationKeys[0].mValue;
//        return;
//    }
//    
//    uint RotationIndex = FindRotation(AnimationTime, pNodeAnim);
//    uint NextRotationIndex = (RotationIndex + 1);
//
//    float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
//    float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
//
//    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
//    const aiQuaternion& EndRotationQ   = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;    
//    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
//    Out = Out.Normalize();
//}
//
//
//void Mesh::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
//{
//    if (pNodeAnim->mNumScalingKeys == 1) {
//        Out = pNodeAnim->mScalingKeys[0].mValue;
//        return;
//    }
//
//    uint ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
//    uint NextScalingIndex = (ScalingIndex + 1);
//
//    float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
//    float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
//
//    const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
//    const aiVector3D& End   = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
//    aiVector3D Delta = End - Start;
//    Out = Start + Factor * Delta;
//}
//
//
//void Mesh::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix& ParentTransform)
//{    
//    string NodeName(pNode->mName.data);
//    
//    const aiAnimation* pAnimation = m_pScene->mAnimations[0];
//        
//    Matrix NodeTransformation(pNode->mTransformation);
//     
//    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
//    
//    if (pNodeAnim) {
//		Matrix result;
//
//
//        // Interpolate translation and generate translation transformation matrix
//        aiVector3D Translation;
//        CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
//        Matrix TranslationM;
//        result.Translate(Translation.x, Translation.y, Translation.z);
//        
//        // Interpolate rotation and generate rotation transformation matrix
//        aiQuaternion RotationQ;
//        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim); 
//		Quaternion qTest = Quaternion(RotationQ.x,RotationQ.y,RotationQ.z,RotationQ.w);
//		result.Rotate(qTest);
//
//		
//		// Interpolate scaling and generate scaling transformation matrix
//        aiVector3D Scaling;
//        CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
//        Matrix ScalingM;
//        result.Scale(Scaling.x, Scaling.y, Scaling.z);
//        
//        
//        // set the above combined transformations
//        NodeTransformation = result;
//    }
//       
//    Matrix GlobalTransformation = ParentTransform * NodeTransformation;
//    
//    if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
//        uint BoneIndex = m_BoneMapping[NodeName];
//        m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * m_BoneInfo[BoneIndex].BoneOffset;
//    }
//    
//    for (uint i = 0 ; i < pNode->mNumChildren ; i++) {
//        ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
//    }
//}


//void Mesh::BoneTransform(float TimeInSeconds, vector<Matrix>& Transforms)
//{
//	Matrix Identity = Matrix::Identity;
//    
//	if(m_pScene->HasAnimations())
//	{
//		float TicksPerSecond = (float)(m_pScene->mAnimations[0]->mTicksPerSecond != 0 ? m_pScene->mAnimations[0]->mTicksPerSecond : 25.0f);
//		float TimeInTicks = TimeInSeconds * TicksPerSecond;
//		float AnimationTime = fmod(TimeInTicks, (float)m_pScene->mAnimations[0]->mDuration);
//
//		ReadNodeHeirarchy(AnimationTime, m_pScene->mRootNode, Identity);
//	}
//
//    Transforms.resize(m_NumBones);
//
//    for (uint i = 0 ; i < m_NumBones ; i++) {
//        Transforms[i] = m_BoneInfo[i].FinalTransformation;
//    }
//}


//const aiNodeAnim* Mesh::FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
//{
//    for (uint i = 0 ; i < pAnimation->mNumChannels ; i++) {
//        const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
//        
//        if (string(pNodeAnim->mNodeName.data) == NodeName) {
//            return pNodeAnim;
//        }
//    }
//    
//    return NULL;
//}