#pragma once
#include "api.h"
#include "fawrek.h"

extern "C" FAWREK_API Fawrek*	FawrekCreate();
extern "C" FAWREK_API int		FawrekInit(Fawrek* pFawrek); 
extern "C" FAWREK_API void		FawrekRender(Fawrek* pFawrek);
extern "C" FAWREK_API void		FawrekDelete(Fawrek* pFawrek);

//extern "C" FAWREK_API void		FawrekCreateModel(Fawrek* pFawrek);
//extern "C" FAWREK_API void		FawrekCreateLight(Fawrek* pFawrek);