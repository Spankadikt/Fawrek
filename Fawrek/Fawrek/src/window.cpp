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
static ICallbacks* g_pCallbacks = NULL;

static bool s_WithDepth = false;
static bool s_WithStencil = false;


static void RenderSceneCB()
{
    g_pCallbacks->RenderSceneCB();
}


static void IdleCB()
{
    g_pCallbacks->RenderSceneCB();
}

static void KeyboardManager(unsigned char _cKey, int _iX, int _iY)
{
	g_pCallbacks->KeyboardManager(_cKey, _iX, _iY);
}

static void InitCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
    glutIdleFunc(IdleCB);
	glutKeyboardFunc(KeyboardManager);
}


void GLUTBackendInit(int _argc, char** _argv, bool _bWithDepth, bool _bWithStencil)
{
    s_WithDepth = _bWithDepth;
    s_WithStencil = _bWithStencil;

    glutInit(&_argc, _argv);
	
    uint uiDisplayMode = GLUT_DOUBLE|GLUT_RGBA;

    if (_bWithDepth) {
        uiDisplayMode |= GLUT_DEPTH;
    }

    if (_bWithStencil) {
        uiDisplayMode |= GLUT_STENCIL;
    }

    glutInitDisplayMode(uiDisplayMode);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}


bool GLUTBackendCreateWindow(unsigned int _iWidth, unsigned int _iHeight, bool _bIsFullScreen, const char* _pcTitle)
{
    if (_bIsFullScreen) {
        char cModeString[64] = { 0 };
        int iBpp = 32;
        _snprintf_s(cModeString, sizeof(cModeString), "%dx%d@%d", _iWidth, _iHeight, iBpp);
        glutGameModeString(cModeString);
        glutEnterGameMode();
    }
    else {
        glutInitWindowSize(_iWidth, _iHeight);
        glutCreateWindow(_pcTitle);
    }

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return false;
    }

    return true;
}

void GLUTBackendRun(ICallbacks* _pCallbacks)
{
    if (!_pCallbacks) {
        fprintf(stderr, "%s : callbacks not specified!\n", __FUNCTION__);
        return;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    if (s_WithDepth) {
        glEnable(GL_DEPTH_TEST);
    }

    g_pCallbacks = _pCallbacks;
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
