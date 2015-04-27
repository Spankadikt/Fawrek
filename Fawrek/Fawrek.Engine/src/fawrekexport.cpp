#include "fawrekexport.h"

Fawrek* FawrekCreate()
{
	return new Fawrek();
}

int FawrekInit(Fawrek* _pFawrek)
{
	if(!_pFawrek->Init())
		return 1;
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