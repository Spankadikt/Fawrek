#include <fawrek.h>

Fawrek::Fawrek()
{   
}

Fawrek::~Fawrek()
{
    Dispose();
}

int Fawrek::Init()
{
	//glewExperimental=GL_TRUE;
	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) 
	{
		printf("ERROR: %s\n",glewGetErrorString(GlewInitResult));
		return 100+GlewInitResult;
	}

	pDirectionalLight = new DirectionalLight();

    pDirectionalLight->m_color = Vector3(1.0f, 1.0f, 1.0f);
    pDirectionalLight->m_fAmbientIntensity = 0.85f;
    pDirectionalLight->m_fDiffuseIntensity = 0.2f;
    pDirectionalLight->m_direction = Vector3(0.0f, 1.0f, 1.0f);     

	pCamera = new Camera();

    pCamera->PerspectiveFOV(120.0f,4/3,0.01f,100.0f);
	pCamera->LookAt(pCamera->pos,pCamera->target,pCamera->up);

	pSkinningRoutine = new SkinningRoutine("shaders/skinningroutine.vs","shaders/skinningroutine.fs");
	//pLightingRoutine = new LightingRoutine("shaders/lightingroutine.vs","shaders/lightingroutine.fs");

	int lightInit = pSkinningRoutine->Init();
	//int lightInit = pLightingRoutine->Init();

	if (lightInit != 0)
	{
		return lightInit;
	}

	//pLightingRoutine->Enable();
	//pLightingRoutine->SetTextureUnit(0);
	//pLightingRoutine->SetDirectionalLight(directionalLight);
	//pLightingRoutine->SetMatSpecularIntensity(1.0f);
	//pLightingRoutine->SetMatSpecularPower(32);

	pSkinningRoutine->Enable();
	pSkinningRoutine->SetTextureUnit(0);
	pSkinningRoutine->SetDirectionalLight(pDirectionalLight);
	pSkinningRoutine->SetMatSpecularIntensity(1.0f);
	pSkinningRoutine->SetMatSpecularPower(32);

	pScene = new Scene();
	pScene->Load("resources/scene_demo.xml");

	/*pModel = new Model("resources/ninja.b3d",Vector3(0.0f,-15.0f,0.0f),Vector3(0.0f,180.0f,0.0f),Vector3(1.5f,1.5f,1.5f),"resources/animation_ninja.xml");
    pModel->m_pAnimation->CrossfadeToClip(18);
    pModel->m_pAnimationBis->CrossfadeToClip(18);*/

	for(int i = 0 ; i < pScene->m_models.size() ; i++ )
	{
		pScene->m_models[i]->m_pAnimation->CrossfadeToClip(18);
		pScene->m_models[i]->m_pAnimationBis->CrossfadeToClip(18);
	}


	return 0;
}

void Fawrek::Dispose()
{
	SAFE_DELETE(pDirectionalLight);
	SAFE_DELETE(pSkinningRoutine);
    SAFE_DELETE(pLightingRoutine);
    SAFE_DELETE(pCamera);
	SAFE_DELETE(pScene);
	//SAFE_DELETE(pModel);
}

void Fawrek::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float runningTime = GetRunningTime();

	for(int i = 0 ; i < pScene->m_models.size() ; i++ )
	{
		//pModel->Render(pCamera,pSkinningRoutine,runningTime);
		pScene->m_models[i]->Render(pCamera,pSkinningRoutine,runningTime);
	}
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
		//pModel->m_pAnimation->CrossfadeToClip(0);
        //pModel->m_pAnimationBis->CrossfadeToClip(0);
	}
	if (_keys[0x42])//Z
	{
		//pModel->m_pAnimation->CrossfadeToClip(18);
        //pModel->m_pAnimationBis->CrossfadeToClip(18);
	}
	if (_keys[0x41])//B
	{
        //pModel->m_pAnimationBis->CrossfadeToClip(2);
        //pModel->m_pAnimationBis->GetLastClip().Init();
        //pModel->m_pAnimationBis->QueueNextClip(&pModel->m_pAnimationBis->GetLastClip());
	}
    if (_keys[0x4E])
	{
		//pModel->m_pAnimation->CrossfadeToClip(2);
        //pModel->m_pAnimation->QueueNextClip(&pModel->m_pAnimation->GetLastClip());
        //pModel->m_pAnimationBis->CrossfadeToClip(2);
        //pModel->m_pAnimationBis->QueueNextClip(&pModel->m_pAnimationBis->GetLastClip());
	}
}

