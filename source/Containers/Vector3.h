//===============================================================================
// @ CVector3.h
// 
// Description
// ------------------------------------------------------------------------------
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//
//
//
//===============================================================================

#ifndef __CVector3__h__
#define __CVector3__h__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class CVector3
{
public:
    // constructor/destructor
    inline CVector3() 
		: x(0.0f), y(0.0f), z(0.0f)
	{
	}
    inline CVector3(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
    {
    }
    //inline ~CVector3() {}

    // copy operations
    CVector3(const CVector3& other);
    CVector3& operator=(const CVector3& other);

    // accessors
    inline float& operator[](unsigned int i)          { return (&x)[i]; }
    inline float operator[](unsigned int i) const { return (&x)[i]; }

    friend float Distance(const CVector3& p0, const CVector3& p1);
    friend float DistanceSquared(const CVector3& p0, const CVector3& p1);

	// Math operators
	float Length() const;
	float LengthSquared() const;
	friend CVector3 Normalize(const CVector3& vector);
	friend float Dot(const CVector3& v1, const CVector3& v2);
	float Dot(const CVector3& vector) const;
	CVector3 Cross(const CVector3& vector) const;
	friend CVector3 Cross(const CVector3& a, const CVector3& b);
	inline CVector3 Inverse();
	friend CVector3 Reflect(const CVector3& v, const CVector3& normal);

    // comparison
    bool operator==(const CVector3& other) const;
    bool operator!=(const CVector3& other) const;
    bool IsZero() const;
    bool IsUnit() const;
	void Ceil();		// Round up all the verticies
	void Floor();		// Round down all the vertices

    // manipulators
    inline void Set(float _x, float _y, float _z);
    void Clean();       // sets near-zero elements to 0
    inline void Zero(); // sets all elements to 0
	inline void Invert();
	void Normalize();
	inline void LerpVector3(const CVector3 to, const float t);

    // operators

    // addition/subtraction
    CVector3 operator+(const CVector3& other) const;
    friend CVector3& operator+=(CVector3& vector, const CVector3& other);
    CVector3 operator-(const CVector3& other) const;
    friend CVector3& operator-=(CVector3& vector, const CVector3& other);

    CVector3 operator-() const;

    // scalar multiplication
    CVector3   operator*(float scalar);
    friend CVector3    operator*(float scalar, const CVector3& vector);
    CVector3&          operator*=(float scalar);
    CVector3   operator/(float scalar);
    CVector3&          operator/=(float scalar);

    // useful defaults
    static CVector3    xAxis;
    static CVector3    yAxis;
    static CVector3    zAxis;
    static CVector3    origin;

    // member variables
    float x, y, z;

protected:

private:
};

//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

// Loads vector3 into SSE register
inline __m128 LoadV3(const CVector3& v)
{
	__m128 x = _mm_load_ss(&v.x);
	__m128 y = _mm_load_ss(&v.y);
	__m128 z = _mm_load_ss(&v.z);
	__m128 xy = _mm_movelh_ps(x, y);
	return _mm_shuffle_ps(xy, z, _MM_SHUFFLE(2, 0, 2, 0));
}

// http://fastcpp.blogspot.ca/2012/02/calculating-length-of-3d-vector-using.html
inline float length3(__m128 v)
{
	// _mm_dp_ps multiply the three lower floats of v with themselves and store 
	// the sum of the product in the lowest float of the result.
	// Since only the lowest float of the result is used, we can use the single 
	// float square root _mm_sqrt_ss and convert the result to the native C++ datatype
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v, v, 0x71)));
}

inline __m128 normalize3(__m128 v)
{
	__m128 inverse_norm = _mm_rsqrt_ps(_mm_dp_ps(v, v, 0x77));
	return _mm_mul_ps(v, inverse_norm);
}

inline __m128 normalize3_accurate(__m128 v)
{
	__m128 norm = _mm_sqrt_ps(_mm_dp_ps(v, v, 0x7F));
	return _mm_div_ps(v, norm);
}

//-------------------------------------------------------------------------------
// @ CVector3::Set()
//-------------------------------------------------------------------------------
// Set vector elements
//-------------------------------------------------------------------------------
inline void 
CVector3::Set(float _x, float _y, float _z)
{
    x = _x; y = _y; z = _z;
}   // End of CVector3::Set()

//-------------------------------------------------------------------------------
// @ CVector3::Zero()
//-------------------------------------------------------------------------------
// Zero all elements
//-------------------------------------------------------------------------------
inline void 
CVector3::Zero()
{
    x = y = z = 0.0f;
}   // End of CVector3::Zero()

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

inline CVector3 CVector3::Inverse()
{
	return CVector3(-x, -y, -z);
}

inline void CVector3::Invert()
{
	x = -x;
	y = -y;
	z = -z;
}

inline void CVector3::LerpVector3(const CVector3 to, const float t)
{
	x = x + (t * (to.x - x));
	y = y + (t * (to.y - y));
	z = z + (t * (to.z - z));
}

inline CVector3 LerpVector3(const CVector3& from, const CVector3 to, const float t)
{
	CVector3 v;
	v.x = from.x + (t * (to.x - from.x));
	v.y = from.y + (t * (to.y - from.y));
	v.z = from.z + (t * (to.z - from.z));
	return v;
}

#endif