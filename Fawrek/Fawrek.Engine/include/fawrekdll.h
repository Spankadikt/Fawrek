#pragma once
#include "api.h"
#include "fawrek.h"

extern "C" FAWREK_API Fawrek*	FawrekCreate();
extern "C" FAWREK_API int		FawrekInit(Fawrek* _pFawrek); 
extern "C" FAWREK_API void		FawrekRender(Fawrek* _pFawrek);
extern "C" FAWREK_API void		FawrekDelete(Fawrek* _pFawrek);

extern "C" FAWREK_API void		ObjectTranslate(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ);
extern "C" FAWREK_API void		ObjectRotate(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ);
extern "C" FAWREK_API void		ObjectScale(Fawrek* _pFawrek, int _nId, float _fX, float _fY, float _fZ);

//extern "C" FAWREK_API void		FawrekCreateModel(Fawrek* pFawrek);
//extern "C" FAWREK_API void		FawrekCreateLight(Fawrek* pFawrek);