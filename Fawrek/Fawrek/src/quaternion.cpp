#include "math.h"

#include "quaternion.h"

#define DELTA 1e-10     // error tolerance used by quaternions

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}


inline float __pitch(const Quaternion& q)
{
	return ::atan2(2.f * (q.y*q.z + q.x*q.w),
		q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z);
}

inline float __yaw(const Quaternion& q)
{
	return ::asin(-2.f * (q.x*q.z - q.y*q.w));
}

inline float __roll(const Quaternion& q)
{
	return ::atan2(2.f * (q.x*q.y + q.z*q.w), 
		q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z);
}

/*Quaternion Quaternion::FromEuler(const Vector3 _rotation)
{
	Quaternion q;
	Vector3 rad = _rotation / 180.f * PI_f;
	//Half cos and half sin
	Vector3 c(
		::cos(0.5f * rad.x),
		::cos(0.5f * rad.y),
		::cos(0.5f * rad.z)
		);
	Vector3 s(
		::sin(0.5f * rad.x),
		::sin(0.5f * rad.y),
		::sin(0.5f * rad.z)
		);

	q.x = s.x*c.y*c.z - c.x*s.y*s.z;
	q.y = c.x*s.y*c.z + s.x*c.y*s.z;
	q.z = c.x*c.y*s.z - s.x*s.y*c.z;
	q.w = c.x*c.y*c.z + s.x*s.y*s.z;
	return q;
}*/

Quaternion Quaternion::FromEuler(float pitch, float yaw, float roll)
{
	Quaternion q;
	yaw = yaw / 180.f * PI_f;
	pitch = pitch / 180.f * PI_f;
	roll = roll / 180.f * PI_f;

	// Assuming the angles are in radians.
	float c1 = cos(yaw/2);
	float s1 = sin(yaw/2);
	float c2 = cos(roll/2);
	float s2 = sin(roll/2);
	float c3 = cos(pitch/2);
	float s3 = sin(pitch/2);

	float c1c2 = c1*c2;
	float c1s2 = c1*s2;
	float s1c2 = s1*c2;
	float s1s2 = s1*s2;

	q.x = c1c2*s3 + s1s2*c3;
	q.y = s1c2*c3 + c1s2*s3;
	q.z = c1s2*c3 - s1c2*s3;
	q.w = c1c2*c3 - s1s2*s3;

	return q;
}

Quaternion Quaternion::FromMatrix(const Matrix _mat)
{
	Quaternion q;
	float trace = _mat.m[0] + _mat.m[5] + _mat.m[10] + 1.0f;
	if( trace > DELTA )
	{
		float s = 0.5f / sqrtf(trace);
		q.w = 0.25f / s;
		q.x = ( _mat.m[6] - _mat.m[9] ) * s;
		q.y = ( _mat.m[8] - _mat.m[2] ) * s;
		q.z = ( _mat.m[1] - _mat.m[4] ) * s;
	}
	else
	{
		if ( _mat.m[0] > _mat.m[5] && _mat.m[0] > _mat.m[10] )
		{
			float s = 2.0f * sqrtf( 1.0f + _mat.m[0] - _mat.m[5] - _mat.m[10]);
			q.w = (_mat.m[9] - _mat.m[6] ) / s;
			q.x = 0.25f * s;
			q.y = (_mat.m[4] + _mat.m[1] ) / s;
			q.z = (_mat.m[8] + _mat.m[2] ) / s;
		}
		else if (_mat.m[5] > _mat.m[10])
		{
			float s = 2.0f * sqrtf( 1.0f + _mat.m[5] - _mat.m[0] - _mat.m[10]);
			q.w = (_mat.m[8] - _mat.m[2] ) / s;
			q.x = (_mat.m[4] + _mat.m[1] ) / s;
			q.y = 0.25f * s;
			q.z = (_mat.m[9] + _mat.m[6] ) / s;
		}
		else
		{
			float s = 2.0f * sqrtf( 1.0f + _mat.m[10] - _mat.m[0] - _mat.m[5] );
			q.w = (_mat.m[4] - _mat.m[1] ) / s;
			q.x = (_mat.m[8] + _mat.m[2] ) / s;
			q.y = (_mat.m[9] + _mat.m[6] ) / s;
			q.z = 0.25f * s;
		}
	}
	return q;
}


Vector3 Quaternion::ToEuler() const
{
	Vector3 v(__pitch(*this), __yaw(*this), __roll(*this));
	return (v / PI_f * 180.f);
}


/*Matrix Quaternion::ToMatrix() const
{
	const Quaternion &q = *this;

	float xx = q.x*q.x;
	float xy = q.x*q.y;
	float xz = q.x*q.z;
	float xw = q.x*q.w;

	float yy = q.y*q.y;
	float yz = q.y*q.z;
	float yw = q.y*q.w;

	float zz = q.z*q.z;
	float zw = q.z*q.w;

	Matrix result;

	result.m[0] = 1.f - 2.f * ( yy + zz );	result.m[4] = 2.f * ( xy + zw );		result.m[8] = 2.f * ( xz - yw );		result.m[12] = 0.f;
	result.m[1] = 2.f * ( xy - zw );		result.m[5] = 1.f - 2.f * ( xx + zz );	result.m[9] = 2.f * ( yz + xw );		result.m[13] = 0.f;
	result.m[2] = 2.f * ( xz + yw );		result.m[6] = 2.f * ( yz - xw );		result.m[10] = 1.f - 2.f * ( xx + yy );	result.m[14] = 0.f;
	result.m[3] = 0.f;						result.m[7] = 0.f;						result.m[11] = 0.f;						result.m[15] = 1.f;	

	return result;
}*/

Matrix Quaternion::ToMatrix() const
{
	const Quaternion &q = *this;

	float x2 = q.x + q.x;
	float y2 = q.y + q.y;
	float z2 = q.z + q.z;

	float wx = q.w*x2;
	float wy = q.w*y2;
	float wz = q.w*z2;

	float xx = q.x*x2;
	float xy = q.x*y2;
	float xz = q.x*z2;

	float yy = q.y*y2;
	float yz = q.y*z2;

	float zz = q.z*z2;

	Matrix result;

	result.m[ 0] = 1.0f - (yy + zz); result.m[ 4] = xy - wz;       result.m[ 8] = xz + wy;      result.m[12] = 0.f;   
	result.m[ 1] = xy + wz;       result.m[ 5] = 1 - (xx + zz); result.m[ 9] = yz - wx;      result.m[13] = 0.f;    
	result.m[ 2] = xz - wy;       result.m[ 6] = yz + wx;       result.m[10]= 1 - (xx + yy); result.m[14] = 0.f;      
	result.m[ 3] = 0;             result.m[ 7] = 0;             result.m[11] = 0;            result.m[15] = 1;

	return result;
}

/** Generate a quaternion by spherically-linearly interpolating between the poses
	\p from	and \p to.
	\param from The source \p from quaternion
	\param to The source \p to quaternion
	\param t In the range of 0 to 1, this value specifies how much to
		interpolate from the \p from quaternion to the \p to quaternion.
*/
Quaternion Quaternion::Slerp(const Quaternion &from, const Quaternion &to, float t)
{
	// Most of this code is optimized for speed and not for readability
	// slerp(p,q,t) = (p*sin((1-t)*omega) + q*sin(t*omega)) / sin(omega)
	Quaternion ret;
	float to1[4];
	float omega, cosom, sinom;
	float scale0, scale1;
	
	// cheap cosine (quaternion dot product)
	// calc cosine
	cosom = from.x*to.x + from.y*to.y + from.z*to.z + from.w*to.w;
	// adjust signs (if necessary)
	if (cosom < 0.0)
	{
		cosom = -cosom;
		to1[0] = -to.x;
		to1[1] = -to.y;
		to1[2] = -to.z;
		to1[3] = -to.w;
	} else  {
		to1[0] = to.x;
		to1[1] = to.y;
		to1[2] = to.z;
		to1[3] = to.w;
	}
	
	// calculate coefficients
	if ((1.0 - cosom) > DELTA) 
	{
		// standard case (slerp)
		omega = acos(cosom);
		sinom = sin(omega);
		scale0 = (float)sin((1.0 - t) * omega) / sinom;
		scale1 = (float)sin(t * omega) / sinom;
	} else {        
		// "from" and "to" quaternions are very close 
		//  ... so we can do a linear interpolation
		scale0 = 1.0f - t;
		scale1 = t;
	}
	
	// calculate final values
	ret.x = scale0*from.x + scale1*to1[0];
	ret.y = scale0*from.y + scale1*to1[1];
	ret.z = scale0*from.z + scale1*to1[2];
	ret.w = scale0*from.w + scale1*to1[3];
	return ret;
}
	
/** Generate a quaternion by linearly interpolating between the poses
	\p from	and \p to.
	\param from The source \p from quaternion
	\param to The source \p to quaternion
	\param t In the range of 0 to 1, this value specifies how much to
		interpolate from the \p from quaternion to the \p to quaternion.
*/
Quaternion Quaternion::Lerp(const Quaternion &from, const Quaternion &to, float t)
{
	// Linearly interpolates between two quaternion positions
	// fast but not as nearly as smooth as Slerp
	Quaternion ret;
	float to1[4];
	float cosom;
	float scale0, scale1;

	// cheap cosine (quaternion dot product)
	// calc cosine
	cosom = from.x*to.x + from.y*to.y + from.z*to.z + from.w*to.w;
    // adjust signs (if necessary)
    if ( cosom < 0.0 )
	{
		to1[0] = - to.x;
		to1[1] = - to.y;
		to1[2] = - to.z;
		to1[3] = - to.w;
    } else  {
		to1[0] = to.x;
		to1[1] = to.y;
		to1[2] = to.z;
		to1[3] = to.w;
    }
 
	// interpolate linearly
    scale0 = 1.0f - t;
    scale1 = t;
 
	// calculate final values
	ret.x = scale0*from.x + scale1*to1[0];
	ret.y = scale0*from.y + scale1*to1[1];
	ret.z = scale0*from.z + scale1*to1[2];
	ret.w = scale0*from.w + scale1*to1[3];
	return ret;
}
