#ifndef QUATERNION_H
#define QUATERNION_H

#include "matrix.h"

class Quaternion
{
public:
	float m_fX,m_fY,m_fZ,m_fW;

	Quaternion();
	Quaternion(float _fX,float _fY,float _fZ,float _fW);

	Quaternion FromEuler(float _fYaw, float _fPitch, float _fRoll);
	Quaternion FromMatrix(const Matrix _mat);
	Vector3 ToEuler() const;
	Matrix ToMatrix() const;

    static Quaternion Lerp(const Quaternion& _from, const Quaternion& _to, float _fTime);
    static Quaternion Slerp(const Quaternion& _from, const Quaternion& _to, float _fTime);
};

#endif //QUATERNION_H