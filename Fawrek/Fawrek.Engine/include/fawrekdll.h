#pragma once
#include "api.h"
#include "fawrek.h"

extern "C" FAWREK_API Fawrek*	FawrekCreate(const char * _sScenePath);
extern "C" FAWREK_API int		FawrekInit(Fawrek* _pFawrek); 
extern "C" FAWREK_API void		FawrekRender(Fawrek* _pFawrek);
extern "C" FAWREK_API void		FawrekDelete(Fawrek* _pFawrek);

extern "C" FAWREK_API void		ObjectSetTranslate(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ);
extern "C" FAWREK_API void		ObjectSetRotate(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ);
extern "C" FAWREK_API void		ObjectSetScale(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ);

extern "C" FAWREK_API void		CameraSetTarget(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ);
extern "C" FAWREK_API void		CameraSetUp(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ);
extern "C" FAWREK_API void		CameraSetFOV(Fawrek* _pFawrek, int _nId, float _fValue);
extern "C" FAWREK_API void		CameraSetNearZ(Fawrek* _pFawrek, int _nId, float _fValue);
extern "C" FAWREK_API void		CameraSetFarZ(Fawrek* _pFawrek, int _nId, float _fValue);
extern "C" FAWREK_API void		CameraSetAspectRatio(Fawrek* _pFawrek, int _nId, float _fValue);

extern "C" FAWREK_API void		LightSetDirection(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ);
extern "C" FAWREK_API void		LightSetColor(Fawrek* _pFawrek, int _nId, float _fR, float _fG, float _fB);
extern "C" FAWREK_API void		LightSetAmbiantIntensity(Fawrek* _pFawrek, int _nId, float _fValue);
extern "C" FAWREK_API void		LightSetDiffuseIntensity(Fawrek* _pFawrek, int _nId, float _fValue);

extern "C" FAWREK_API void		ClipCrossfade(Fawrek* _pFawrek, int _nCharacterId, int _nAnimationId, int _nBodyPart);

//extern "C" FAWREK_API void		FawrekCreateModel(Fawrek* pFawrek);
//extern "C" FAWREK_API void		FawrekCreateLight(Fawrek* pFawrek);