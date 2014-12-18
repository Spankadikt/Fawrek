#ifndef WINDOW_H
#define	WINDOW_H

#include "types.h"
#include "callbacks.h"

void GLUTBackendInit(int _argc, char **_argv, bool _withDepth, bool _withStencil);

bool GLUTBackendCreateWindow(uint _width, uint _height, bool _isFullScreen, const char *_pTitle);

void GLUTBackendRun(ICallbacks *_pCallbacks);

#endif //WINDOW_H