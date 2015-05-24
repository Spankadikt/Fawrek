#include "object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Translate(Vector3 _vTranslation)
{
	m_translation = _vTranslation;
}

void Object::Translate(float _fTranslationX, float _fTranslationY, float _fTranslationZ)
{
	Vector3 vTranslation = Vector3(_fTranslationX,_fTranslationY,_fTranslationZ);
	Translate(vTranslation);
}

void Object::Rotate(Vector3 _vRotation)
{
	m_rotation = _vRotation;
}
	
void Object::Rotate(float _fRotateX, float _fRotateY, float _fRotateZ)
{
	Vector3 vRotation = Vector3(_fRotateX,_fRotateY,_fRotateZ);
	Rotate(vRotation);
}

void Object::Scale(Vector3 _vScale)
{
	m_scale = _vScale;
}
	
void Object::Scale(float _fScaleX, float _fScaleY, float _fScaleZ)
{
	Vector3 vScale = Vector3(_fScaleX,_fScaleY,_fScaleZ);
	Scale(vScale);
}