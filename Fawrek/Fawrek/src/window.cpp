#ifndef WIN32
#include "unistd.h"
#endif
#include "stdio.h"
#include "glew.h"
#include "freeglut.h"

#include "utils.h"
#include "window.h"

// Points to the object implementing the ICallbacks interface which was delivered to
// GLUTBackendRun(). All events are forwarded to this object.
static ICallbacks* pCallbacks = NULL;

static bool sWithDepth = false;
static bool sWithStencil = false;


static void RenderSceneCB()
{
    pCallbacks->RenderSceneCB();
}


static void IdleCB()
{
    pCallbacks->RenderSceneCB();
}

static void KeyboardManager(unsigned char key, int x, int y)
{
	pCallbacks->KeyboardManager(key, x, y);
}

static void InitCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
    glutIdleFunc(IdleCB);
	glutKeyboardFunc(KeyboardManager);
}


void GLUTBackendInit(int _argc, char **_argv, bool _withDepth, bool _withStencil)
{
    sWithDepth = _withDepth;
    sWithStencil = _withStencil;

    glutInit(&_argc, _argv);
	
    uint displayMode = GLUT_DOUBLE|GLUT_RGBA;

    if (_withDepth) {
        displayMode |= GLUT_DEPTH;
    }

    if (_withStencil) {
        displayMode |= GLUT_STENCIL;
    }

    glutInitDisplayMode(displayMode);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}


bool GLUTBackendCreateWindow(unsigned int _width, unsigned int _height, bool _isFullScreen, const char *_pTitle)
{
    if (_isFullScreen) {
        char ModeString[64] = { 0 };
        int bpp = 32;
        _snprintf_s(ModeString, sizeof(ModeString), "%dx%d@%d", _width, _height, bpp);
        glutGameModeString(ModeString);
        glutEnterGameMode();
    }
    else {
        glutInitWindowSize(_width, _height);
        glutCreateWindow(_pTitle);
    }

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return false;
    }

    return true;
}

void GLUTBackendRun(ICallbacks *_pCallbacks)
{
    if (!_pCallbacks) {
        fprintf(stderr, "%s : callbacks not specified!\n", __FUNCTION__);
        return;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    if (sWithDepth) {
        glEnable(GL_DEPTH_TEST);
    }

    pCallbacks = _pCallbacks;
    InitCallbacks();
    glutMainLoop();
}


void GLUTBackendSwapBuffers()
{
    glutSwapBuffers();
}

void GLUTBackendLeaveMainLoop()
{
    glutLeaveMainLoop();
}
