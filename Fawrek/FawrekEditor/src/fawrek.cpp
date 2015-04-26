#include <fawrek.h>

Fawrek::Fawrek()
{   
}

Fawrek::~Fawrek()
{
    Dispose();
}

bool Fawrek::Init()
{
    directionalLight.m_color = Vector3(1.0f, 1.0f, 1.0f);
    directionalLight.m_fAmbientIntensity = 0.85f;
    directionalLight.m_fDiffuseIntensity = 0.2f;
    directionalLight.m_direction = Vector3(0.0f, 1.0f, 1.0f);     

	pCamera = new Camera();

    pCamera->PerspectiveFOV(120.0f,4/3,0.01f,100.0f);
	pCamera->LookAt(pCamera->pos,pCamera->target,pCamera->up);

	pLight = new Light("shaders/skinning.vs","shaders/skinning.fs");

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
    pModel->m_pAnimation->CrossfadeToClip(18);
    pModel->m_pAnimationBis->CrossfadeToClip(18);

	return true;
}

void Fawrek::Dispose()
{
    SAFE_DELETE(pLight);
    SAFE_DELETE(pCamera);
	SAFE_DELETE(pModel);
}

void Fawrek::Render()
{
    float runningTime = GetRunningTime();

	pModel->Render(pCamera,pLight,runningTime);
}

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

void Fawrek::KeyboardManager(bool _keys[256])
{	
	if (_keys[0x41])//A
	{
		pModel->m_pAnimation->CrossfadeToClip(0);
        pModel->m_pAnimationBis->CrossfadeToClip(0);
	}
	if (_keys[0x42])//Z
	{
		pModel->m_pAnimation->CrossfadeToClip(18);
        pModel->m_pAnimationBis->CrossfadeToClip(18);
	}
	if (_keys[0x41])//B
	{
        pModel->m_pAnimationBis->CrossfadeToClip(2);
        pModel->m_pAnimationBis->GetLastClip().Init();
        pModel->m_pAnimationBis->QueueNextClip(&pModel->m_pAnimationBis->GetLastClip());
	}
    if (_keys[0x4E])
	{
		pModel->m_pAnimation->CrossfadeToClip(2);
        pModel->m_pAnimation->QueueNextClip(&pModel->m_pAnimation->GetLastClip());
        pModel->m_pAnimationBis->CrossfadeToClip(2);
        pModel->m_pAnimationBis->QueueNextClip(&pModel->m_pAnimationBis->GetLastClip());
	}
}

