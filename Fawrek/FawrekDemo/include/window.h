#ifndef WINDOW_H
#define	WINDOW_H

#include "types.h"
#include "callbacks.h"

void GLUTBackendInit(int _iArgc, char** _argv, bool _bWithDepth, bool _bWithStencil);
bool GLUTBackendCreateWindow(uint _uiWidth, uint _uiHeight, bool _bIsFullScreen, const char* _pcTitle);
void GLUTBackendRun(ICallbacks* _pCallbacks);

#endif //WINDOW_H