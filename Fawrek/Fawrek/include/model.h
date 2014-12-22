#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "camera.h"
#include "light.h"
#include "engine.h"
#include "quaternion.h"

class Model
{
public:
	Model(const std::string &_filename);
	Model(const std::string &_filename, Vector3 _vTranslate, Vector3 _vRotate, Vector3 _vScale);
	~Model();

	void Render(Camera *_camera, Light *_shader, float _runningTime);

	Mesh mesh;

	Vector3 vScale;
	Vector3 vRotate;
	Vector3 vTranslate;
};

#endif //MESH_H

