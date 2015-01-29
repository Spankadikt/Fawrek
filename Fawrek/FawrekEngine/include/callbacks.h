#include "api.h"

#ifndef CALLBACKS_H
#define CALLBACKS_H

class FAWREK_API ICallbacks
{
public:
    virtual void RenderSceneCB() {};
	virtual void KeyboardManager(unsigned char _cKey, int _iX, int _iY) {};
};


#endif //CALLBACKS_H