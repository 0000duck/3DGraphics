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
    inline CVector3() {}
    inline CVector3(float _x, float _y, float _z) :
        x(_x), y(_y), z(_z)
    {
    }
    inline ~CVector3() {}

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
	float Dot(const CVector3& vector) const;
	CVector3 Cross(const CVector3& vector) const;
	friend CVector3 Cross(const CVector3& a, const CVector3& b);
	inline CVector3 Inverse();

    // comparison
    bool operator==(const CVector3& other) const;
    bool operator!=(const CVector3& other) const;
    bool IsZero() const;
    bool IsUnit() const;

    // manipulators
    inline void Set(float _x, float _y, float _z);
    void Clean();       // sets near-zero elements to 0
    inline void Zero(); // sets all elements to 0
	inline void Invert();
	void Normalize();

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

#endif
