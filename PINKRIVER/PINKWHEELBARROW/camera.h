#ifndef CAMERA_H
#define CAMERA_H

#include "pr_vector3.h"
#include "pr_matrix.h"

class Camera
{
public:

    Camera();
    Camera(const Vector3 _pos, const Vector3 _target, const Vector3 _up);
	~Camera();

    Vector3 GetPos()	const { return pos;		}
    Vector3 GetTarget() const { return target;	}
    Vector3 GetUp()		const { return up;		}

	void Set(Vector3 _pos, Vector3 _target, Vector3 _up);

	void PerspectiveFOV(float _fovAngle, float _aspectRation, float _nearZ, float _farZ);
	void LookAt(Vector3 _pos, Vector3 _target, Vector3 _up);

	Matrix view;
	Matrix projection;

private:


    Vector3 pos;
    Vector3 target;
    Vector3 up;
};

#endif	/* CAMERA_H */
