#include "fawrekdll.h"

Fawrek* FawrekCreate(const char * _sScenePath)
{
	return new Fawrek(_sScenePath);
}

int FawrekInit(Fawrek* _pFawrek)
{
	int initResult = _pFawrek->Init();
	if(initResult != 0)
		return initResult;
	else
		return 0;
}

void FawrekRender(Fawrek* _pFawrek)
{
	_pFawrek->Render();
}

void FawrekDelete(Fawrek* _pFawrek)
{
	delete _pFawrek;
}

void ObjectRotate(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ)
{
	_pFawrek->pScene->m_pObjectManager->GetObjectById(_nId)->Rotate(_fX,_fY,_fZ);
}

void ObjectTranslate(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ)
{
	_pFawrek->pScene->m_pObjectManager->GetObjectById(_nId)->Translate(_fX,_fY,_fZ);
}

void ObjectScale(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ)
{
	_pFawrek->pScene->m_pObjectManager->GetObjectById(_nId)->Scale(_fX,_fY,_fZ);
}

void CameraSetTarget(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ)
{
	Camera* cam =_pFawrek->pScene->m_pObjectManager->GetCamera();
	Vector3 target = Vector3(_fX,_fY,_fZ);

	cam->LookAt(cam->m_translation,target,cam->m_up);
}

void CameraSetUp(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ)
{
	Camera* cam =_pFawrek->pScene->m_pObjectManager->GetCamera();
	Vector3 up = Vector3(_fX,_fY,_fZ);

	cam->LookAt(cam->m_translation,cam->m_target,up);
}

void CameraSetFOV(Fawrek* _pFawrek, int _nId, float _fValue)
{
	Camera* cam =_pFawrek->pScene->m_pObjectManager->GetCamera();
	cam->PerspectiveFOV(_fValue,cam->m_fAspectRation,cam->m_fNearZ,cam->m_fFarZ);
}

void CameraSetNearZ(Fawrek* _pFawrek, int _nId, float _fValue)
{
	Camera* cam =_pFawrek->pScene->m_pObjectManager->GetCamera();
	cam->PerspectiveFOV(cam->m_fFovAngle,cam->m_fAspectRation,_fValue,cam->m_fFarZ);
}

void CameraSetFarZ(Fawrek* _pFawrek, int _nId, float _fValue)
{
	Camera* cam =_pFawrek->pScene->m_pObjectManager->GetCamera();
	cam->PerspectiveFOV(cam->m_fFovAngle,cam->m_fAspectRation,cam->m_fNearZ,_fValue);
}

void CameraSetAspectRatio(Fawrek* _pFawrek, int _nId, float _fValue)
{
	Camera* cam =_pFawrek->pScene->m_pObjectManager->GetCamera();
	cam->PerspectiveFOV(cam->m_fFovAngle,_fValue,cam->m_fNearZ,cam->m_fFarZ);
}

void LightSetDirection(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ)
{
	_pFawrek->pScene->m_pObjectManager->GetDirectionalLight()->SetDirection(_fX,_fY,_fZ);

	//TODO light manager with a function that refreshes lights
	_pFawrek->pLightingRoutine->Enable();
	_pFawrek->pLightingRoutine->SetDirectionalLight(_pFawrek->pScene->m_pObjectManager->GetDirectionalLight());

	_pFawrek->pSkinningRoutine->Enable();
	_pFawrek->pSkinningRoutine->SetDirectionalLight(_pFawrek->pScene->m_pObjectManager->GetDirectionalLight());
}

void LightSetColor(Fawrek* _pFawrek, int _nId, float _fR, float _fG, float _fB)
{
	_pFawrek->pScene->m_pObjectManager->GetDirectionalLight()->SetColor(_fR,_fG,_fB);

	_pFawrek->pLightingRoutine->Enable();
	_pFawrek->pLightingRoutine->SetDirectionalLight(_pFawrek->pScene->m_pObjectManager->GetDirectionalLight());

	_pFawrek->pSkinningRoutine->Enable();
	_pFawrek->pSkinningRoutine->SetDirectionalLight(_pFawrek->pScene->m_pObjectManager->GetDirectionalLight());
}

void LightSetAmbiantIntensity(Fawrek* _pFawrek, int _nId, float _fValue)
{
	_pFawrek->pScene->m_pObjectManager->GetDirectionalLight()->m_fAmbientIntensity = _fValue;

	_pFawrek->pLightingRoutine->Enable();
	_pFawrek->pLightingRoutine->SetDirectionalLight(_pFawrek->pScene->m_pObjectManager->GetDirectionalLight());

	_pFawrek->pSkinningRoutine->Enable();
	_pFawrek->pSkinningRoutine->SetDirectionalLight(_pFawrek->pScene->m_pObjectManager->GetDirectionalLight());
}

void LightSetDiffuseIntensity(Fawrek* _pFawrek, int _nId, float _fValue)
{
	_pFawrek->pScene->m_pObjectManager->GetDirectionalLight()->m_fDiffuseIntensity = _fValue;

	_pFawrek->pLightingRoutine->Enable();
	_pFawrek->pLightingRoutine->SetDirectionalLight(_pFawrek->pScene->m_pObjectManager->GetDirectionalLight());

	_pFawrek->pSkinningRoutine->Enable();
	_pFawrek->pSkinningRoutine->SetDirectionalLight(_pFawrek->pScene->m_pObjectManager->GetDirectionalLight());
}