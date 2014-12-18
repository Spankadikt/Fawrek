#include "model.h"

Model::Model()
{
	pMesh = new Mesh();
}

Model::~Model()
{
	delete pMesh;
}

