#ifndef PR_MATHS_
#define	PR_MATHS_


struct Vector3
{
	float x;
	float y;
	float z;

	Vector3()
	{
	}

	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

#endif