#include <fawrek.h>

Fawrek::Fawrek()
{
	m_mouseLeftButton._bClicked = false;
}

Fawrek::~Fawrek()
{
    Dispose();
}

int Fawrek::Init()
{
	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) 
	{
		printf("ERROR: %s\n",glewGetErrorString(GlewInitResult));
		return 100+GlewInitResult;
	}

	int initGlResult = InitGL();
	if(initGlResult != 1)
		return initGlResult;
	
	pScene = new Scene();
	pScene->Load("resources/scene_demo_heavy.xml");

	pPickingTexture = new PickingTexture();

	if(!pPickingTexture->Init(640,480))
		return 30;

	pSkinningRoutine = new SkinningRoutine("shaders/skinningroutine.vs","shaders/skinningroutine.fs");
	pLightingRoutine = new LightingRoutine("shaders/lightingroutine.vs","shaders/lightingroutine.fs");
	pColoringRoutine = new ColoringRoutine("shaders/coloringroutine.vs","shaders/coloringroutine.fs");
	pPickingRoutine = new PickingRoutine("shaders/pickingroutine.vs","shaders/pickingroutine.fs");

	int skinInit = pSkinningRoutine->Init();
	int lightInit = pLightingRoutine->Init();
	int colorInit = pColoringRoutine->Init();
	int pickInit = pPickingRoutine->Init();

	if (skinInit != 0)
		return skinInit;

	if (lightInit != 0)
		return lightInit;

	if (pickInit != 0)
		return pickInit;

	if (colorInit != 0)
		return colorInit;


	pColoringRoutine->Enable();

	pLightingRoutine->Enable();
	pLightingRoutine->SetTextureUnit(0);
	pLightingRoutine->SetDirectionalLight(pScene->m_pObjectManager->GetDirectionalLight());
	pLightingRoutine->SetMatSpecularIntensity(1.0f);
	pLightingRoutine->SetMatSpecularPower(32);

	pSkinningRoutine->Enable();
	pSkinningRoutine->SetTextureUnit(0);
	pSkinningRoutine->SetDirectionalLight(pScene->m_pObjectManager->GetDirectionalLight());
	pSkinningRoutine->SetMatSpecularIntensity(1.0f);
	pSkinningRoutine->SetMatSpecularPower(32);

	for(int i = 0 ; i < pScene->m_pObjectManager->GetModels().size() ; i++ )
	{
		Model* pModel = static_cast<Model*>(pScene->m_pObjectManager->GetModels()[i]);
		if(pModel->m_pScene->HasAnimations())
		{
			pModel->m_pAnimation->CrossfadeToClip(0);
			//pModel->m_pAnimationBis->CrossfadeToClip(0);
		}
	}


	return 0;
}

void Fawrek::Dispose()
{
	SAFE_DELETE(pSkinningRoutine);
    SAFE_DELETE(pLightingRoutine);
	SAFE_DELETE(pColoringRoutine);
	SAFE_DELETE(pPickingRoutine);
	SAFE_DELETE(pScene);
}

void Fawrek::Render()
{


	float runningTime = GetRunningTime();

	//picking
	pPickingTexture->EnableWriting();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pPickingRoutine->Enable();

	for(int i = 0 ; i < pScene->m_pObjectManager->GetModels().size() ; i++ )
	{
        pPickingRoutine->SetObjectIndex(i);
		pScene->m_pObjectManager->GetModels()[i]->Render(pScene->m_pObjectManager->GetCamera(),pPickingRoutine,runningTime);
    }

    pPickingTexture->DisableWriting(); 


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//coloring?
	if(m_mouseLeftButton._bClicked)
	{
		Pixel = pPickingTexture->ReadPixel(m_mouseLeftButton._nX, 480 - m_mouseLeftButton._nY - 1);

		for(int i = 0 ; i < pScene->m_pObjectManager->GetModels().size() ; i++ )
		{
			pScene->m_pObjectManager->GetModels()[i]->m_bSelected = false;
		}

        if (Pixel.PrimID != 0)
		{
			pScene->m_pObjectManager->GetModels()[Pixel.ObjectID]->m_bSelected = true;
        }

		m_mouseLeftButton._bClicked = false;
	}

	//rendering
	for(int i = 0 ; i < pScene->m_pObjectManager->GetModels().size() ; i++ )
	{
		Model *pModel = pScene->m_pObjectManager->GetModels()[i];
		if(true)
		{
			if(pModel->m_bSelected)
			{
				pColoringRoutine->Enable();
				pModel->Render(pScene->m_pObjectManager->GetCamera(),pColoringRoutine,runningTime);
			}
			else
			{
				if(pModel->m_pScene->HasAnimations())
				{
					pSkinningRoutine->Enable();
					pModel->Render(pScene->m_pObjectManager->GetCamera(),pSkinningRoutine,runningTime);
				}
				else
				{
					pLightingRoutine->Enable();
					pModel->Render(pScene->m_pObjectManager->GetCamera(),pLightingRoutine,runningTime);
				}
			}
		}
		else
		{
			if(pModel->m_bSelected)
			{	
				for(int i=0;i<pModel->m_pMesh->m_entries.size();i++)
				{
					Matrix modelMatrix = Matrix::Identity;

					modelMatrix.Translate(pModel->m_translation);
					Quaternion qRotate = qRotate.FromEuler(pModel->m_rotation.m_fX,pModel->m_rotation.m_fY,pModel->m_rotation.m_fZ);
					modelMatrix.Rotate(qRotate);
					modelMatrix.Scale(pModel->m_scale);

					Matrix modelView = pScene->m_pObjectManager->GetCamera()->view * modelMatrix;
					Matrix viewProjection = pScene->m_pObjectManager->GetCamera()->projection * modelView;

					if(i==(int)Pixel.DrawID)
					{
						pColoringRoutine->Enable();

						pColoringRoutine->SetWVP(viewProjection);
						pColoringRoutine->SetWorldMatrix(modelMatrix);


						pModel->m_pMesh->PickingRender((int)Pixel.ObjectID,i,(int)Pixel.PrimID);
					}
					else
					{
						pSkinningRoutine->Enable();

						pSkinningRoutine->SetWVP(viewProjection);
						pSkinningRoutine->SetWorldMatrix(modelMatrix);

						pModel->m_pMesh->PickingRender((int)Pixel.ObjectID,i,(int)Pixel.PrimID);
					}
				}
			}
			else
			{
				pSkinningRoutine->Enable();
				pModel->Render(pScene->m_pObjectManager->GetCamera(),pSkinningRoutine,runningTime);
			}
		}
		
	}
}

int Fawrek::InitGL()
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE;										// Initialization Went OK
}

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

void Fawrek::MouseManager(int _nX,int _nY)
{
	m_mouseLeftButton._bClicked = true;
	m_mouseLeftButton._nX = _nX;
	m_mouseLeftButton._nY = _nY;
}

