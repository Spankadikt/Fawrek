#include "api.h"

#ifndef OBJECT_H
#define OBJECT_H

#include "vector3.h"

class FAWREK_API Object
{
public:
	Object();
	~Object();

	void Translate(Vector3 _vTranslation);
	void Translate(float _fTranslationX, float _fTranslationY, float _fTranslationZ);

	void Rotate(Vector3 _vRotation);
	void Rotate(float _fRotateX, float _fRotateY, float _fRotateZ);

	void Scale(Vector3 _vScale);
	void Scale(float _fScaleX, float _fScaleY, float _fScaleZ);

	int m_id;

	Vector3 m_scale;
	Vector3 m_rotation;
	Vector3 m_translation;
protected:

};
#endif//OBJECT_H