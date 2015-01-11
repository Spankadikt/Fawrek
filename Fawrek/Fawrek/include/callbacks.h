#ifndef CALLBACKS_H
#define CALLBACKS_H

class ICallbacks
{
public:
    virtual void RenderSceneCB() {};
	virtual void KeyboardManager(unsigned char key, int x, int y) {};
};


#endif //CALLBACKS_H