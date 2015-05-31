#include "api.h"

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

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class FAWREK_API Animation
{
public:

    enum BodyPart
    {
        FULL_BODY,
        UPPER_BODY,
        LOWER_BODY
    };

	Animation(const aiScene* _pScene, Mesh* _pMesh, Matrix _globalInverseTransform, BodyPart _bodyPartAffected);
	~Animation();

	void CalcInterpolatedScaling(aiVector3D& _out, float _fAnimationTime, const aiNodeAnim* _pNodeAnim);
    void CalcInterpolatedRotation(aiQuaternion& _out, float _fAnimationTime, const aiNodeAnim* _pNodeAnim);
    void CalcInterpolatedPosition(aiVector3D& _out, float _fAnimationTime, const aiNodeAnim* _pNodeAnim);

    uint FindScaling(float _fAnimationTime, const aiNodeAnim* _pNodeAnim);
    uint FindRotation(float _fAnimationTime, const aiNodeAnim* _pNodeAnim);
    uint FindPosition(float _fAnimationTime, const aiNodeAnim* _pNodeAnim);

    const aiNodeAnim* FindNodeAnim(const aiAnimation* _pAnimation, const string _sNodeName);
    void ReadNodeHierarchy(const aiNode* _pNode, const Matrix& _parentTransform, bool _crossFade);
	void BoneTransform(float _fTimeInSeconds, vector<Matrix>& _transforms);
    Matrix CalcInterpolations(const aiNodeAnim* _pNodeAnim, bool _crossFade);
	
    void SetCurrentClip(Clip* _clip);
    Clip &GetCurrentClip();
    void SetLastClip(Clip* _clip);
    Clip &GetLastClip();
    void CrossfadeToClip(int _iNum);
    void CrossfadeToClip(Clip* _clip);
    void QueueNextClip(Clip* _clip);
	void InitCrossfade();

    void LoadClips(const std::string& _sFilename);
	void LoadBonePack(tinyxml2::XMLNode *_pNode,NodePack *_pNodePack);
    void PlayClip();

    const aiScene* m_pScene;

	Clip* m_pCurrentClip;
    Clip* m_pLastClip;
    Clip* m_pNextClip;

private:
    BodyPart bodyPartAffected;

	Mesh* m_pMesh;

    float m_fWeight;
	float m_fStartCrossfade;

	Matrix m_GlobalInverseTransform;

    int m_iNbClip;
    vector<Clip> m_clips;

    NodePack* m_pNodePack;
};

#endif // ANIMATION_H