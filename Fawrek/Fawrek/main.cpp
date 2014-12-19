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
		//pLight->SetEyeWorldPos(pCamera->pos);
		pLight->SetMatSpecularIntensity(1.0f);
		pLight->SetMatSpecularPower(32);

		//pMesh = new Mesh();
		if (!mesh.LoadMesh("boblampclean.md5mesh")) {
            printf("Mesh load failed\n");
            return false;            
        }

        //return mesh.LoadMesh("phoenix_ugv.md2");
		return true;
    }

    void Run()
    {
        GLUTBackendRun(this);
    }

	void RenderSceneCB()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pLight->Enable();

		vector<Matrix> Transforms;
               
        float RunningTime = GetRunningTime();

        mesh.BoneTransform(RunningTime, Transforms);
        
        for (uint i = 0 ; i < Transforms.size() ; i++) {
            pLight->SetBoneTransform(i, Transforms[i]);
        }

		/*static float Scale = 0.0f;

		Scale += 0.01f;*/

		Matrix modelMatrix = Matrix::Identity;

		//float n = 2 * cos(Scale);
		Vector3 scale = Vector3(0.3f,0.3f,0.3f);
		Quaternion rotate = Quaternion(0.0f,0.0f,0.0f,1.0f);
		Vector3 translate = Vector3(0.0f,0.0f,0.0f);

		modelMatrix.Scale(scale);
		modelMatrix.Rotate(rotate);
		modelMatrix.Translate(translate);

		Matrix modelView = pCamera->view * modelMatrix;
		Matrix viewProjection = pCamera->projection * modelView;
		
		pLight->SetWVP(viewProjection);
        pLight->SetWorldMatrix(modelMatrix);

		mesh.Render();

		glutSwapBuffers();
	}

private:
    Light *pLight;
    Camera *pCamera;
	Mesh mesh;
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