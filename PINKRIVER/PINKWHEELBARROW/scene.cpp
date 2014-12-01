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

const Matrix &Scene::GetWorldTrans(Camera cam)
{
    Matrix ScaleTrans, RotateTrans, TranslationTrans, CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

    ScaleTrans.Scale(scale.x, scale.y, scale.z);
    RotateTrans.Rotate(rotateInfo.x, rotateInfo.y, rotateInfo.z);
    TranslationTrans.Translate(worldPos.x, worldPos.y, worldPos.z);
	
	CameraTranslationTrans.Translate(-cam.GetPos().x, -cam.GetPos().y, -cam.GetPos().z);  
	cam.LookAt(cam.GetPos(), cam.GetTarget(), cam.GetUp());
	CameraRotateTrans = cam.view;
	cam.PerspectiveFOV(90.0f, 1024/768, 1.0f, 100.f);
	PersProjTrans = cam.projection;

	Wtransformation = cam.projection * cam.view * CameraTranslationTrans * TranslationTrans * RotateTrans * ScaleTrans;
    return Wtransformation;
}

/*const Matrix &Scene::GetWPTrans(Camera cam)
{
    Matrix ScaleTrans, RotateTrans, TranslationTrans;

    ScaleTrans.Scale(scale.x, scale.y, scale.z);
    RotateTrans.Rotate(rotateInfo.x, rotateInfo.y, rotateInfo.z);
    TranslationTrans.Translate(worldPos.x, worldPos.y, worldPos.z);

	Wtransformation = cam.projection * TranslationTrans * RotateTrans * ScaleTrans;
    return Wtransformation;
}*/

const Matrix &Scene::GetVPTrans(Camera cam)
{
    Matrix CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

	CameraTranslationTrans.Translate(-cam.GetPos().x, -cam.GetPos().y, -cam.GetPos().z);
	//CameraRotateTrans.InitCameraTransform(cam.GetTarget(), cam.GetUp());
    
	VPtransformation = cam.projection * cam.view * CameraTranslationTrans;
    return VPtransformation;
}

const Matrix &Scene::GetWVPTrans(Camera cam)
{
    //GetWorldTrans();
    GetVPTrans(cam);

    WVPtransformation = VPtransformation * Wtransformation;
    return WVPtransformation;
}