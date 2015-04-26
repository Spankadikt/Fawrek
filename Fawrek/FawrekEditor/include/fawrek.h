#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "quaternion.h"
#include "model.h"
#include "utils.h"
#include "camera.h"
#include "texture.h"
#include "engine.h"
#include "light.h"

using namespace std;

#define WINDOW_WIDTH  1024//1920
#define WINDOW_HEIGHT 768//1200

class Fawrek : public Engine
{
public:

    Fawrek();
    ~Fawrek();

    bool Init();
    void Dispose();
    void Render();

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

	/*virtual void KeyboardManager(unsigned char key, int x, int y)
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
	}*/

private:
    Light *pLight;
    Camera *pCamera;
	Model *pModel;
    DirectionalLight directionalLight;
};
