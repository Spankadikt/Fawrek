#include "fawrekdll.h"

Fawrek* FawrekCreate()
{
	return new Fawrek();
}

int FawrekInit(Fawrek* _pFawrek)
{
	int initResult = _pFawrek->Init();
	if(initResult != 0)
		return initResult;
	else
		return 0;
}

void FawrekRender(Fawrek* _pFawrek)
{
	_pFawrek->Render();
}

void FawrekDelete(Fawrek* _pFawrek)
{
	delete _pFawrek;
}