#include "api.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "scene.h"
#include "quaternion.h"
#include "model.h"
#include "utils.h"
#include "camera.h"
#include "texture.h"
#include "engine.h"
#include "lightingroutine.h"
#include "skinningroutine.h"
#include "coloringroutine.h"
#include "pickingroutine.h"
#include "pickingtexture.h"

using namespace std;

#define WINDOW_WIDTH  1024//1920
#define WINDOW_HEIGHT 768//1200

class FAWREK_API Fawrek : public Engine
{
public:

    Fawrek();
	Fawrek(const std::string& _sSceneFilename);
    ~Fawrek();

    int Init();
	int InitGL();
    void Dispose();
    void Render();
	void Update();
    /*void Run()
    {
        GLUTBackendRun(this);
    }*/

	/*virtual void RenderSceneCB()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Render();
        
		glutSwapBuffers();
	}*/

	Scene *pScene;

	void KeyboardManager(bool _keys[256]);
	void MouseManager(int _nX,int _nY);

	struct
	{
		int _nX;
		int _nY;
		bool _bClicked;
	} m_mouseLeftButton;

	LightingRoutine *pLightingRoutine;
	SkinningRoutine *pSkinningRoutine;

private:

	ColoringRoutine *pColoringRoutine;
	PickingRoutine *pPickingRoutine;
	PickingTexture *pPickingTexture;
	PickingTexture::PixelInfo Pixel;

	std::string m_sSceneFilename;
};
