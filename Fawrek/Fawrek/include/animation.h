#ifndef ANIMATION_H
#define ANIMATION_H

#include "map"
#include "vector"

#include "utils.h"
#include "matrix.h"
#include "skeleton.h"
#include "mesh.h"
#include "tinyxml2.h"
#include "clip.h"

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
    void ReadNodeHierarchy(const aiNode* pNode, const Matrix& ParentTransform, bool _crossFade);
	void BoneTransform(float TimeInSeconds, vector<Matrix>& Transforms);
    Matrix CalcInterpolations(const aiNodeAnim* pNodeAnim, bool _crossFade);
	
    void SetCurrentClip(Clip *_clip);
    //void SetCurrentClipAndPlay(int num);
    Clip &GetCurrentClip();
    //void SetNextClip(int num);
    void SetNextClipAndPlay(int num);
    Clip &GetNextClip();

	void InitCrossfade();

    void LoadClips(const std::string &_filename);
    void PlayClip();

    const aiScene *pScene;

private:
	Mesh *pMesh;

	Clip *currentClip;
    Clip *nextClip;

    float weight;
	float startCrossfade;

	Matrix m_GlobalInverseTransform;

    int nbClip;
    vector<Clip> clips;
};

#endif // ANIMATION_H