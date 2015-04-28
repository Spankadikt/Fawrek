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
    }

    ~Fawrek()
    {
        Dispose();
    }

    bool Init()
    {
        directionalLight.m_color = Vector3(1.0f, 1.0f, 1.0f);
        directionalLight.m_fAmbientIntensity = 0.85f;
        directionalLight.m_fDiffuseIntensity = 0.2f;
        directionalLight.m_direction = Vector3(0.0f, 1.0f, 1.0f);     

		pCamera = new Camera();

        pCamera->PerspectiveFOV(120.0f,4/3,0.01f,100.0f);
		pCamera->LookAt(pCamera->pos,pCamera->target,pCamera->up);

		pLight = new Light("shaders/skinning.vs","shaders/skinning.fs");

		int initLight = pLight->Init();
		if (initLight != 0 )
		{
			return false;
		}

		pLight->Enable();
		pLight->SetTextureUnit(0);
		pLight->SetDirectionalLight(directionalLight);
		pLight->SetMatSpecularIntensity(1.0f);
		pLight->SetMatSpecularPower(32);

		pModel = new Model("resources/ninja.b3d",Vector3(0.0f,-15.0f,0.0f),Vector3(0.0f,180.0f,0.0f),Vector3(1.5f,1.5f,1.5f),"resources/animation_ninja.xml");
        pModel->m_pAnimation->CrossfadeToClip(18);
        pModel->m_pAnimationBis->CrossfadeToClip(18);

		return true;
    }

    void Dispose()
    {
        SAFE_DELETE(pLight);
        SAFE_DELETE(pCamera);
		SAFE_DELETE(pModel);
    }

    void Render()
    {
        float runningTime = GetRunningTime();

		pModel->Render(pCamera,pLight,runningTime);
    }

    void Run()
    {
        GLUTBackendRun(this);
    }

	virtual void RenderSceneCB()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Render();
        
		glutSwapBuffers();
	}

	virtual void KeyboardManager(unsigned char key, int x, int y)
	{	
		switch (key)
		{
		case 'a':
			pModel->m_pAnimation->CrossfadeToClip(0);
            pModel->m_pAnimationBis->CrossfadeToClip(0);
			break;
		case 'z':
			pModel->m_pAnimation->CrossfadeToClip(18);
            pModel->m_pAnimationBis->CrossfadeToClip(18);
			break;
		case 'b':
            pModel->m_pAnimationBis->CrossfadeToClip(2);
            pModel->m_pAnimationBis->GetLastClip().Init();
            pModel->m_pAnimationBis->QueueNextClip(&pModel->m_pAnimationBis->GetLastClip());
			break;
        case 'n':
			pModel->m_pAnimation->CrossfadeToClip(2);
            pModel->m_pAnimation->QueueNextClip(&pModel->m_pAnimation->GetLastClip());
            pModel->m_pAnimationBis->CrossfadeToClip(2);
            pModel->m_pAnimationBis->QueueNextClip(&pModel->m_pAnimationBis->GetLastClip());
			break;
		default:
			break;
		}	 
	}

private:
    Light *pLight;
    Camera *pCamera;
	Model *pModel;
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