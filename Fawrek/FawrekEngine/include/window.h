#include "api.h"

#ifndef WINDOW_H
#define	WINDOW_H

#include "types.h"
#include "callbacks.h"

void FAWREK_API GLUTBackendInit(int _iArgc, char** _argv, bool _bWithDepth, bool _bWithStencil);
bool FAWREK_API GLUTBackendCreateWindow(uint _uiWidth, uint _uiHeight, bool _bIsFullScreen, const char* _pcTitle);
void FAWREK_API GLUTBackendRun(ICallbacks* _pCallbacks);

#endif //WINDOW_H