#include "math.h"

#include "quaternion.h"

#define DELTA 1e-10     // error tolerance used by quaternions

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	m_fX = _x;
	m_fY = _y;
	m_fZ = _z;
	m_fW = _w;
}


inline float __pitch(const Quaternion& _q)
{
	return ::atan2(2.f * (_q.m_fY*_q.m_fZ + _q.m_fX*_q.m_fW),
		_q.m_fW*_q.m_fW - _q.m_fX*_q.m_fX - _q.m_fY*_q.m_fY + _q.m_fZ*_q.m_fZ);
}

inline float __yaw(const Quaternion& _q)
{
	return ::asin(-2.f * (_q.m_fX*_q.m_fZ - _q.m_fY*_q.m_fW));
}

inline float __roll(const Quaternion& _q)
{
	return ::atan2(2.f * (_q.m_fX*_q.m_fY + _q.m_fZ*_q.m_fW), 
		_q.m_fW*_q.m_fW + _q.m_fX*_q.m_fX - _q.m_fY*_q.m_fY - _q.m_fZ*_q.m_fZ);
}

Quaternion Quaternion::FromEuler(float _fPitch, float _fYaw, float _fRoll)
{
	Quaternion q;
	_fYaw = _fYaw / 180.f * PI_f;
	_fPitch = _fPitch / 180.f * PI_f;
	_fRoll = _fRoll / 180.f * PI_f;

	// Assuming the angles are in radians.
	float c1 = cos(_fYaw/2);
	float s1 = sin(_fYaw/2);
	float c2 = cos(_fRoll/2);
	float s2 = sin(_fRoll/2);
	float c3 = cos(_fPitch/2);
	float s3 = sin(_fPitch/2);

	float c1c2 = c1*c2;
	float c1s2 = c1*s2;
	float s1c2 = s1*c2;
	float s1s2 = s1*s2;

	q.m_fX = c1c2*s3 + s1s2*c3;
	q.m_fY = s1c2*c3 + c1s2*s3;
	q.m_fZ = c1s2*c3 - s1c2*s3;
	q.m_fW = c1c2*c3 - s1s2*s3;

	return q;
}

Quaternion Quaternion::FromMatrix(const Matrix _mat)
{
	Quaternion q;
	float trace = _mat.m_m[0] + _mat.m_m[5] + _mat.m_m[10] + 1.0f;
	if( trace > DELTA )
	{
		float s = 0.5f / sqrtf(trace);
		q.m_fW = 0.25f / s;
		q.m_fX = ( _mat.m_m[6] - _mat.m_m[9] ) * s;
		q.m_fY = ( _mat.m_m[8] - _mat.m_m[2] ) * s;
		q.m_fZ = ( _mat.m_m[1] - _mat.m_m[4] ) * s;
	}
	else
	{
		if ( _mat.m_m[0] > _mat.m_m[5] && _mat.m_m[0] > _mat.m_m[10] )
		{
			float s = 2.0f * sqrtf( 1.0f + _mat.m_m[0] - _mat.m_m[5] - _mat.m_m[10]);
			q.m_fW = (_mat.m_m[9] - _mat.m_m[6] ) / s;
			q.m_fX = 0.25f * s;
			q.m_fY = (_mat.m_m[4] + _mat.m_m[1] ) / s;
			q.m_fZ = (_mat.m_m[8] + _mat.m_m[2] ) / s;
		}
		else if (_mat.m_m[5] > _mat.m_m[10])
		{
			float s = 2.0f * sqrtf( 1.0f + _mat.m_m[5] - _mat.m_m[0] - _mat.m_m[10]);
			q.m_fW = (_mat.m_m[8] - _mat.m_m[2] ) / s;
			q.m_fX = (_mat.m_m[4] + _mat.m_m[1] ) / s;
			q.m_fY = 0.25f * s;
			q.m_fZ = (_mat.m_m[9] + _mat.m_m[6] ) / s;
		}
		else
		{
			float s = 2.0f * sqrtf( 1.0f + _mat.m_m[10] - _mat.m_m[0] - _mat.m_m[5] );
			q.m_fW = (_mat.m_m[4] - _mat.m_m[1] ) / s;
			q.m_fX = (_mat.m_m[8] + _mat.m_m[2] ) / s;
			q.m_fY = (_mat.m_m[9] + _mat.m_m[6] ) / s;
			q.m_fZ = 0.25f * s;
		}
	}
	return q;
}


Vector3 Quaternion::ToEuler() const
{
	Vector3 v(__pitch(*this), __yaw(*this), __roll(*this));
	return (v / PI_f * 180.f);
}

Matrix Quaternion::ToMatrix() const
{
	const Quaternion &q = *this;

	float x2 = q.m_fX + q.m_fX;
	float y2 = q.m_fY + q.m_fY;
	float z2 = q.m_fZ + q.m_fZ;

	float wx = q.m_fW*x2;
	float wy = q.m_fW*y2;
	float wz = q.m_fW*z2;

	float xx = q.m_fX*x2;
	float xy = q.m_fX*y2;
	float xz = q.m_fX*z2;

	float yy = q.m_fY*y2;
	float yz = q.m_fY*z2;

	float zz = q.m_fZ*z2;

	Matrix result;

	result.m_m[ 0] = 1.0f - (yy + zz); result.m_m[ 4] = xy - wz;       result.m_m[ 8] = xz + wy;      result.m_m[12] = 0.f;   
	result.m_m[ 1] = xy + wz;       result.m_m[ 5] = 1 - (xx + zz); result.m_m[ 9] = yz - wx;      result.m_m[13] = 0.f;    
	result.m_m[ 2] = xz - wy;       result.m_m[ 6] = yz + wx;       result.m_m[10]= 1 - (xx + yy); result.m_m[14] = 0.f;      
	result.m_m[ 3] = 0;             result.m_m[ 7] = 0;             result.m_m[11] = 0;            result.m_m[15] = 1;

	return result;
}

/** Generate a quaternion by spherically-linearly interpolating between the poses
	\p from	and \p to.
	\param from The source \p from quaternion
	\param to The source \p to quaternion
	\param t In the range of 0 to 1, this value specifies how much to
		interpolate from the \p from quaternion to the \p to quaternion.
*/
Quaternion Quaternion::Slerp(const Quaternion& _from, const Quaternion& _to, float _fTime)
{
	// Most of this code is optimized for speed and not for readability
	// slerp(p,q,t) = (p*sin((1-t)*omega) + q*sin(t*omega)) / sin(omega)
	Quaternion ret;
	float to1[4];
	float omega, cosom, sinom;
	float scale0, scale1;
	
	// cheap cosine (quaternion dot product)
	// calc cosine
	cosom = _from.m_fX*_to.m_fX + _from.m_fY*_to.m_fY + _from.m_fZ*_to.m_fZ + _from.m_fW*_to.m_fW;
	// adjust signs (if necessary)
	if (cosom < 0.0)
	{
		cosom = -cosom;
		to1[0] = -_to.m_fX;
		to1[1] = -_to.m_fY;
		to1[2] = -_to.m_fZ;
		to1[3] = -_to.m_fW;
	} else  {
		to1[0] = _to.m_fX;
		to1[1] = _to.m_fY;
		to1[2] = _to.m_fZ;
		to1[3] = _to.m_fW;
	}
	
	// calculate coefficients
	if ((1.0 - cosom) > DELTA) 
	{
		// standard case (slerp)
		omega = acos(cosom);
		sinom = sin(omega);
		scale0 = (float)sin((1.0 - _fTime) * omega) / sinom;
		scale1 = (float)sin(_fTime * omega) / sinom;
	} else {        
		// "from" and "to" quaternions are very close 
		//  ... so we can do a linear interpolation
		scale0 = 1.0f - _fTime;
		scale1 = _fTime;
	}
	
	// calculate final values
	ret.m_fX = scale0*_from.m_fX + scale1*to1[0];
	ret.m_fY = scale0*_from.m_fY + scale1*to1[1];
	ret.m_fZ = scale0*_from.m_fZ + scale1*to1[2];
	ret.m_fW = scale0*_from.m_fW + scale1*to1[3];

	return ret;
}
	
/** Generate a quaternion by linearly interpolating between the poses
	\p from	and \p to.
	\param from The source \p from quaternion
	\param to The source \p to quaternion
	\param t In the range of 0 to 1, this value specifies how much to
		interpolate from the \p from quaternion to the \p to quaternion.
*/
Quaternion Quaternion::Lerp(const Quaternion& _from, const Quaternion& _to, float _fTime)
{
	// Linearly interpolates between two quaternion positions
	// fast but not as nearly as smooth as Slerp
	Quaternion ret;
	float to1[4];
	float cosom;
	float scale0, scale1;

	// cheap cosine (quaternion dot product)
	// calc cosine
	cosom = _from.m_fX*_to.m_fX + _from.m_fY*_to.m_fY + _from.m_fZ*_to.m_fZ + _from.m_fW*_to.m_fW;
    // adjust signs (if necessary)
    if ( cosom < 0.0 )
	{
		to1[0] = - _to.m_fX;
		to1[1] = - _to.m_fY;
		to1[2] = - _to.m_fZ;
		to1[3] = - _to.m_fW;
    } else  {
		to1[0] = _to.m_fX;
		to1[1] = _to.m_fY;
		to1[2] = _to.m_fZ;
		to1[3] = _to.m_fW;
    }
 
	// interpolate linearly
    scale0 = 1.0f - _fTime;
    scale1 = _fTime;
 
	// calculate final values
	ret.m_fX = scale0*_from.m_fX + scale1*to1[0];
	ret.m_fY = scale0*_from.m_fY + scale1*to1[1];
	ret.m_fZ = scale0*_from.m_fZ + scale1*to1[2];
	ret.m_fW = scale0*_from.m_fW + scale1*to1[3];

	return ret;
}
