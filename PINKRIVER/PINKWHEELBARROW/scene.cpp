#include "scene.h"

Scene::Scene()
{
	scale      = Vector3(1.0f, 1.0f, 1.0f);
    worldPos   = Vector3(0.0f, 0.0f, 0.0f);
    rotateInfo = Vector3(0.0f, 0.0f, 0.0f);
}

Scene::~Scene()
{
}

void Scene::Scale(float s)
{
    Scale(s, s, s);
}
    
    
void Scene::Scale(const Vector3 &scale)
{
    Scale(scale.x, scale.y, scale.z);
}
    
void Scene::Scale(float ScaleX, float ScaleY, float ScaleZ)
{
    scale.x = ScaleX;
    scale.y = ScaleY;
    scale.z = ScaleZ;
}

void Scene::WorldPos(float x, float y, float z)
{
    worldPos.x = x;
    worldPos.y = y;
    worldPos.z = z;
}
    
void Scene::WorldPos(const Vector3 &Pos)
{
    worldPos = Pos;
}

void Scene::Rotate(float RotateX, float RotateY, float RotateZ)
{
    rotateInfo.x = RotateX;
    rotateInfo.y = RotateY;
    rotateInfo.z = RotateZ;
}
    
void Scene::Rotate(const Vector3 &r)
{
    Rotate(r.x, r.y, r.z);
}

const Matrix &Scene::GetWorldTrans()
{
    Matrix ScaleTrans, RotateTrans, TranslationTrans;

    ScaleTrans.Scale(scale.x, scale.y, scale.z);
    RotateTrans.Rotate(rotateInfo.x, rotateInfo.y, rotateInfo.z);
    TranslationTrans.Translate(worldPos.x, worldPos.y, worldPos.z);

    Wtransformation = TranslationTrans * RotateTrans * ScaleTrans;
    return Wtransformation;
}