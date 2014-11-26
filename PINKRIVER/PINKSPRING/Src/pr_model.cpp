#include "pr_model.h"

Model::Model()
{
	mesh = Mesh();
}

Model::~Model()
{

}

Mesh *Model::getMesh()
{
	return &mesh;
}

