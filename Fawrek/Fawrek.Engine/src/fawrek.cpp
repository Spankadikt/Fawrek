#include <fawrek.h>

Fawrek::Fawrek()
{
	m_mouseLeftButton._bClicked = false;
	//m_sSceneFilename = "resources/scene_demo_light_test.xml";
	m_sSceneFilename = "resources/scene_demo_heavy.xml";
}

Fawrek::Fawrek(const std::string& _sSceneFilename)
{
	m_mouseLeftButton._bClicked = false;
	m_sSceneFilename = _sSceneFilename;
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
	pScene->Load(m_sSceneFilename);

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

	for(int i = 0 ; i < pScene->m_pObjectManager->GetCharacters().size() ; i++ )
 	{
		pPickingRoutine->SetObjectIndex(pScene->m_pObjectManager->GetModels().size() + i);
		pScene->m_pObjectManager->GetCharacters()[i]->Render(pScene->m_pObjectManager->GetCamera(),pPickingRoutine,runningTime);
    }
 
    pPickingTexture->DisableWriting();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//coloring
	if(m_mouseLeftButton._bClicked)
	{
		Pixel = pPickingTexture->ReadPixel(m_mouseLeftButton._nX, 480 - m_mouseLeftButton._nY - 1);

		for(int i = 0 ; i < pScene->m_pObjectManager->GetModels().size() ; i++ )
		{
			pScene->m_pObjectManager->GetModels()[i]->m_bSelected = false;
		}

		for(int i = 0 ; i < pScene->m_pObjectManager->GetCharacters().size() ; i++ )
		{
			pScene->m_pObjectManager->GetCharacters()[i]->m_bSelected = false;
		}

        if (Pixel.PrimID != 0)
		{
			if((int)Pixel.ObjectID < pScene->m_pObjectManager->GetModels().size())
			{
				pScene->m_pObjectManager->GetModels()[Pixel.ObjectID]->m_bSelected = true;
			}
			else
			{
				pScene->m_pObjectManager->GetCharacters()[Pixel.ObjectID - pScene->m_pObjectManager->GetModels().size()]->m_bSelected = true;
			}
        }
 
		m_mouseLeftButton._bClicked = false;
	}

	//rendering
	for(int i = 0 ; i < pScene->m_pObjectManager->GetModels().size() ; i++ )
	{
		if(pScene->m_pObjectManager->GetModels()[i]->m_bSelected)
		{
			pColoringRoutine->Enable();
			pScene->m_pObjectManager->GetModels()[i]->Render(pScene->m_pObjectManager->GetCamera(),pColoringRoutine,runningTime);
		}
		else
		{
			pLightingRoutine->Enable();
			pScene->m_pObjectManager->GetModels()[i]->Render(pScene->m_pObjectManager->GetCamera(),pLightingRoutine,runningTime);
		}
	}

	for(int i = 0 ; i < pScene->m_pObjectManager->GetCharacters().size() ; i++ )
	{
		bool bAnimationStoped = pScene->m_pObjectManager->GetCharacters()[i]->m_pAnimation->GetCurrentClip().m_state == Clip::ClipState::STOP;
		bool bAnimationBisStoped = pScene->m_pObjectManager->GetCharacters()[i]->m_pAnimationBis->GetCurrentClip().m_state == Clip::ClipState::STOP;
		if(bAnimationStoped && bAnimationBisStoped)
		{
			bool bFullPicking = false;
			if(bFullPicking)
			{
				if(pScene->m_pObjectManager->GetCharacters()[i]->m_bSelected)
				{
					pColoringRoutine->Enable();
					pScene->m_pObjectManager->GetCharacters()[i]->Render(pScene->m_pObjectManager->GetCamera(),pColoringRoutine,runningTime);
				}
				else
				{
					pLightingRoutine->Enable();
					pScene->m_pObjectManager->GetCharacters()[i]->Render(pScene->m_pObjectManager->GetCamera(),pLightingRoutine,runningTime);
				}
			}
			else
			{
				if(pScene->m_pObjectManager->GetCharacters()[i]->m_bSelected)
				{	
					for(int j=0;j<pScene->m_pObjectManager->GetCharacters()[i]->m_pMesh->m_entries.size();j++)
					{
						Matrix modelMatrix = Matrix::Identity;
						Character* pCharacter = pScene->m_pObjectManager->GetCharacters()[i];

						modelMatrix.Translate(pCharacter->m_translation);
						Quaternion qRotate = qRotate.FromEuler(pCharacter->m_rotation.m_fX,pCharacter->m_rotation.m_fY,pCharacter->m_rotation.m_fZ);
						modelMatrix.Rotate(qRotate);
						modelMatrix.Scale(pCharacter->m_scale);

						Matrix modelView = pScene->m_pObjectManager->GetCamera()->view * modelMatrix;
						Matrix viewProjection = pScene->m_pObjectManager->GetCamera()->projection * modelView;

						if(j==(int)Pixel.DrawID)
						{
							pColoringRoutine->Enable();

							pColoringRoutine->SetWVP(viewProjection);
							pColoringRoutine->SetWorldMatrix(modelMatrix);


							pCharacter->m_pMesh->PickingRender((int)Pixel.ObjectID,j,(int)Pixel.PrimID);
						}
						else
						{
							pLightingRoutine->Enable();

							pLightingRoutine->SetWVP(viewProjection);
							pLightingRoutine->SetWorldMatrix(modelMatrix);

							pCharacter->m_pMesh->PickingRender((int)Pixel.ObjectID,j,(int)Pixel.PrimID);
						}
					}
				}
				else
				{
					pLightingRoutine->Enable();
					pScene->m_pObjectManager->GetCharacters()[i]->Render(pScene->m_pObjectManager->GetCamera(),pLightingRoutine,runningTime);
				}
			}
		}
		else
		{
			pSkinningRoutine->Enable();
			pScene->m_pObjectManager->GetCharacters()[i]->Render(pScene->m_pObjectManager->GetCamera(),pSkinningRoutine,runningTime);
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
		for(int i = 0 ; i < pScene->m_pObjectManager->GetCharacters().size() ; i++ )
		{
			pScene->m_pObjectManager->GetCharacters()[i]->m_pAnimation->CrossfadeToClip(0);
			pScene->m_pObjectManager->GetCharacters()[i]->m_pAnimationBis->CrossfadeToClip(0);
		}
	}
	if (_keys[0x5A])//Z
	{
		for(int i = 0 ; i < pScene->m_pObjectManager->GetCharacters().size() ; i++ )
		{
			pScene->m_pObjectManager->GetCharacters()[i]->m_pAnimation->CrossfadeToClip(18);
			pScene->m_pObjectManager->GetCharacters()[i]->m_pAnimationBis->CrossfadeToClip(18);
		}
	}
	if (_keys[0x45])//E
	{
		for(int i = 0 ; i < pScene->m_pObjectManager->GetCharacters().size() ; i++ )
		{
			if(pScene->m_pObjectManager->GetCharacters()[i]->m_pAnimationBis->GetCurrentClip().m_iId != 2)
			{
				pScene->m_pObjectManager->GetCharacters()[i]->m_pAnimationBis->CrossfadeToClip(2);
				pScene->m_pObjectManager->GetCharacters()[i]->m_pAnimationBis->QueueNextClip(pScene->m_pObjectManager->GetCharacters()[i]->m_pAnimationBis->GetLastClip().m_iId);
			}
		}
	}
}

void Fawrek::MouseManager(int _nX,int _nY)
{
	m_mouseLeftButton._bClicked = true;
	m_mouseLeftButton._nX = _nX;
	m_mouseLeftButton._nY = _nY;
}

