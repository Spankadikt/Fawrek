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