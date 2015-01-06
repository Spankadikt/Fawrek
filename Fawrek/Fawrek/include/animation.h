#ifndef ANIMATION_H
#define ANIMATION_H

#include "map"
#include "vector"

#include "utils.h"
#include "matrix.h"
#include "skeleton.h"
#include "mesh.h"

#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"

class Animation
{

public:
	Animation(const aiScene *_pScene, Mesh *_pMesh, Matrix _globalInverseTransform);
	~Animation();

	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

    uint FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
    uint FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
    uint FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);

    const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
    void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix& ParentTransform);
	void BoneTransform(float TimeInSeconds, vector<Matrix>& Transforms);

private:
	Mesh *pMesh;
	const aiScene *pScene;

	Matrix m_GlobalInverseTransform;
};

#endif // ANIMATION_H