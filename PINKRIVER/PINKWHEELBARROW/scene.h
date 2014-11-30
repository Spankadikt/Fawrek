#ifndef SCENE_H
#define SCENE_H

#include "pr_matrix.h"
#include "camera.h"

class Scene
{
public:

    Scene();
	~Scene();

	void Scale(float s);
	void Scale(const Vector3 &scale);
	void Scale(float scaleX, float scaleY, float scaleZ);

	void WorldPos(float x, float y, float z);
	void WorldPos(const Vector3 &Post);
	
	void Rotate(float rotateX, float rotateY, float rotateZ);
	void Rotate(const Vector3 &r);

	const Matrix &GetWorldTrans();

private:
	Vector3 scale;
	Vector3 worldPos;
	Vector3 rotateInfo;

	Matrix Wtransformation;
};

#endif	/* CAMERA_H */