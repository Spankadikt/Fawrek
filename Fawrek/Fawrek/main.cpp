#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "quaternion.h"
#include "model.h"
#include "utils.h"
#include "camera.h"
#include "texture.h"
#include "window.h"
#include "engine.h"
#include "light.h"

using namespace std;

#define WINDOW_WIDTH  1024//1920
#define WINDOW_HEIGHT 768//1200

class Fawrek : public ICallbacks, public Engine
{
public:

    Fawrek()
    {
        directionalLight.Color = Vector3(1.0f, 1.0f, 1.0f);
        directionalLight.AmbientIntensity = 0.85f;
        directionalLight.DiffuseIntensity = 0.2f;
        directionalLight.Direction = Vector3(0.0f, 1.0f, 1.0f);        
    }

    ~Fawrek()
    {
        SAFE_DELETE(pLight);
        SAFE_DELETE(pCamera);
		SAFE_DELETE(pModel);
		//SAFE_DELETE(pModel2);
		//SAFE_DELETE(pModel3);
    }

    bool Init()
    {
		pCamera = new Camera();

        pCamera->PerspectiveFOV(120.0f,4/3,0.01f,100.0f);
		pCamera->LookAt(pCamera->pos,pCamera->target,pCamera->up);

		pLight = new Light();

		if (!pLight->Init())
		{
			return false;
		}

		pLight->Enable();
		pLight->SetTextureUnit(0);
		pLight->SetDirectionalLight(directionalLight);
		pLight->SetMatSpecularIntensity(1.0f);
		pLight->SetMatSpecularPower(32);

		pModel = new Model("resources/ninja.b3d",Vector3(0.0f,-15.0f,0.0f),Vector3(0.0f,180.0f,0.0f),Vector3(1.5f,1.5f,1.5f),"resources/animation_ninja.xml");
        pModel->pAnimation->SetCurrentClipAndPlay(0);
		//pModel2 = new Model("resources/dwarf1.b3d",Vector3(15.0f,-15.0f,0.0f),Vector3(0.0f,180.0f,0.0f),Vector3(0.3f,0.3f,0.3f));
		//pModel3 = new Model("resources/boblampclean.md5mesh",Vector3(0.0f,-15.0f,0.0f),Vector3(90.0f,0.0f,0.0f),Vector3(0.3f,0.3f,0.3f));

		return true;
    }

    void Run()
    {
        GLUTBackendRun(this);
    }

	virtual void RenderSceneCB()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float runningTime = GetRunningTime();

		pModel->Render(pCamera,pLight,runningTime);
		//pModel2->Render(pCamera,pLight,runningTime);
		//pModel3->Render(pCamera,pLight,runningTime);

		glutSwapBuffers();
	}

	virtual void KeyboardManager(unsigned char key, int x, int y)
	{	
		switch (key)
		{
		case 'a':
			pModel->pAnimation->SetCurrentClipAndPlay(0);
			break;
		case 'z':
			pModel->pAnimation->SetCurrentClipAndPlay(1);
			break;
		case ' ':
			pModel->pAnimation->SetCurrentClipAndPlay(2);
			break;
		default:
			break;
		}	 
	}

private:
    Light *pLight;
    Camera *pCamera;
	Model *pModel;
	//Model *pModel2;
	//Model *pModel3;
    DirectionalLight directionalLight;
};

int main(int argc, char *argv[])
{
   	GLUTBackendInit(argc, argv, true, false);

    if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, "Fawrek")) {
        return 1;
    }

	SRANDOM;

    Fawrek *pApp = new Fawrek();

    if (!pApp->Init()) {
        return 1;
    }

    pApp->Run();

    delete pApp;
 
    return 0;
}