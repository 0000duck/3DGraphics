//===============================================================================
// @ CVector3.cpp
// 
// 3D vector class
// ------------------------------------------------------------------------------
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "stdafx.h"
#include "Vector3.h"
#include "Utility/MiniMath.h"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

CVector3 CVector3::xAxis(1.0f, 0.0f, 0.0f);
CVector3 CVector3::yAxis(0.0f, 1.0f, 0.0f);
CVector3 CVector3::zAxis(0.0f, 0.0f, 1.0f);
CVector3 CVector3::origin(0.0f, 0.0f, 0.0f);

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ CVector3::CVector3()
//-------------------------------------------------------------------------------
// Copy constructor
//-------------------------------------------------------------------------------
CVector3::CVector3(const CVector3& other) : 
    x(other.x),
    y(other.y),
    z(other.z)
{

}   // End of CVector3::CVector3()


//-------------------------------------------------------------------------------
// @ CVector3::operator=()
//-------------------------------------------------------------------------------
// Assignment operator
//-------------------------------------------------------------------------------
CVector3&
CVector3::operator=(const CVector3& other)
{
    // if same object
    if (this == &other)
        return *this;
        
    x = other.x;
    y = other.y;
    z = other.z;
    
    return *this;

}   // End of CVector3::operator=()





//-------------------------------------------------------------------------------
// @ ::Distance()
//-------------------------------------------------------------------------------
// Point distance
//-------------------------------------------------------------------------------
float 
Distance(const CVector3& p0, const CVector3& p1)
{
    float x = p0.x - p1.x;
    float y = p0.y - p1.y;
    float z = p0.z - p1.z;

    return ::IvSqrt(x*x + y*y + z*z);

}   // End of CVector3::Length()


//-------------------------------------------------------------------------------
// @ ::DistanceSquared()
//-------------------------------------------------------------------------------
// Point distance
//-------------------------------------------------------------------------------
float 
DistanceSquared(const CVector3& p0, const CVector3& p1)
{
    float x = p0.x - p1.x;
    float y = p0.y - p1.y;
    float z = p0.z - p1.z;

    return (x*x + y*y + z*z);

}   // End of ::DistanceSquared()


//-------------------------------------------------------------------------------
// @ CVector3::Length()
//-------------------------------------------------------------------------------
// Returns the length of the vector.
//-------------------------------------------------------------------------------
float CVector3::Length() const
{
	return (sqrt(Dot(CVector3(x, y, z))));

} // End of ::Length()


//-------------------------------------------------------------------------------
// @ CVector3::LengthSquared()
//-------------------------------------------------------------------------------
// Returns the length squared of the vector.
//-------------------------------------------------------------------------------
float CVector3::LengthSquared() const
{
	float len = Length();
	return (len * len);

} // End of ::LengthSquared()


//-------------------------------------------------------------------------------
// @ CVector3::Normalize()
//-------------------------------------------------------------------------------
// Normalizes the vector to unit length.
//-------------------------------------------------------------------------------
void CVector3::Normalize()
{
	float len = Length();
	x /= len;
	y /= len;
	z /= len;

} // End of ::Normalize()

CVector3 Normalize(const CVector3& vector)
{
	float len = vector.Length();
	return CVector3(vector.x / len, 
					vector.y / len, 
					vector.z / len);
}

float Dot(const CVector3& v1, const CVector3& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

//-------------------------------------------------------------------------------
// @ CVector3::Dot(const CVector3& vector) const
//-------------------------------------------------------------------------------
// Returns the dot product of the given vector with the current one.
//-------------------------------------------------------------------------------
float CVector3::Dot(const CVector3& vector) const
{
	return ((vector.x * vector.x) + 
			(vector.y * vector.y) + 
			(vector.z * vector.z));

} // End of ::Dot()


//-------------------------------------------------------------------------------
// @ CVector3::Cross(const CVector3& vector) const
//-------------------------------------------------------------------------------
// Returns the cross product of the given vector with the current one.
//-------------------------------------------------------------------------------
CVector3 CVector3::Cross(const CVector3& vector) const
{
	float i = (y * vector.z) - (vector.y * z);
	float j = (z * vector.x) - (vector.z * x);
	float k = (x * vector.y) - (vector.x * y);
	return (CVector3(i, j, k));

} // End of ::Cross()

CVector3 Cross(const CVector3& a, const CVector3& b)
{
	return a.Cross(b);
}

CVector3 Reflect(const CVector3& v, const CVector3& normal)
{
	CVector3 temp = Dot(v, normal) * normal;
	return CVector3(v - (2.0f * temp));
}

//-------------------------------------------------------------------------------
// @ CVector3::operator==()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
CVector3::operator==(const CVector3& other) const
{
    if (::IvAreEqual(other.x, x)
        && ::IvAreEqual(other.y, y)
        && ::IvAreEqual(other.z, z))
        return true;

    return false;   
}   // End of CVector3::operator==()


//-------------------------------------------------------------------------------
// @ CVector3::operator!=()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
CVector3::operator!=(const CVector3& other) const
{
    if (::IvAreEqual(other.x, x)
        && ::IvAreEqual(other.y, y)
        && ::IvAreEqual(other.z, z))
        return false;

    return true;
}   // End of CVector3::operator!=()


//-------------------------------------------------------------------------------
// @ CVector3::IsZero()
//-------------------------------------------------------------------------------
// Check for zero vector
//-------------------------------------------------------------------------------
bool 
CVector3::IsZero() const
{
    return ::IsZero(x*x + y*y + z*z);

}   // End of CVector3::IsZero()


//-------------------------------------------------------------------------------
// @ CVector3::IsUnit()
//-------------------------------------------------------------------------------
// Check for unit vector
//-------------------------------------------------------------------------------
bool 
CVector3::IsUnit() const
{
    return ::IsZero(1.0f - x*x - y*y - z*z);

}   // End of CVector3::IsUnit()

void CVector3::Ceil()
{
	x = ceilf(x);
	y = ceilf(y);
	z = ceilf(z);
}

void CVector3::Floor()
{
	x = floorf(x);
	y = floorf(y);
	z = floorf(z);
}

//-------------------------------------------------------------------------------
// @ CVector3::Clean()
//-------------------------------------------------------------------------------
// Set elements close to zero equal to zero
//-------------------------------------------------------------------------------
void
CVector3::Clean()
{
    if (::IsZero(x))
        x = 0.0f;
    if (::IsZero(y))
        y = 0.0f;
    if (::IsZero(z))
        z = 0.0f;

}   // End of CVector3::Clean()




//-------------------------------------------------------------------------------
// @ CVector3::operator+()
//-------------------------------------------------------------------------------
// Add vector to self and return
//-------------------------------------------------------------------------------
CVector3 
CVector3::operator+(const CVector3& other) const
{
    return CVector3(x + other.x, y + other.y, z + other.z);

}   // End of CVector3::operator+()


//-------------------------------------------------------------------------------
// @ CVector3::operator+=()
//-------------------------------------------------------------------------------
// Add vector to self, store in self
//-------------------------------------------------------------------------------
CVector3& 
operator+=(CVector3& self, const CVector3& other)
{
    self.x += other.x;
    self.y += other.y;
    self.z += other.z;

    return self;

}   // End of CVector3::operator+=()


//-------------------------------------------------------------------------------
// @ CVector3::operator-()
//-------------------------------------------------------------------------------
// Subtract vector from self and return
//-------------------------------------------------------------------------------
CVector3 
CVector3::operator-(const CVector3& other) const
{
    return CVector3(x - other.x, y - other.y, z - other.z);

}   // End of CVector3::operator-()


//-------------------------------------------------------------------------------
// @ CVector3::operator-=()
//-------------------------------------------------------------------------------
// Subtract vector from self, store in self
//-------------------------------------------------------------------------------
CVector3& 
operator-=(CVector3& self, const CVector3& other)
{
    self.x -= other.x;
    self.y -= other.y;
    self.z -= other.z;

    return self;

}   // End of CVector3::operator-=()

//-------------------------------------------------------------------------------
// @ CVector3::operator-=() (unary)
//-------------------------------------------------------------------------------
// Negate self and return
//-------------------------------------------------------------------------------
CVector3
CVector3::operator-() const
{
    return CVector3(-x, -y, -z);
}    // End of CVector3::operator-()


//-------------------------------------------------------------------------------
// @ operator*()
//-------------------------------------------------------------------------------
// Scalar multiplication
//-------------------------------------------------------------------------------
CVector3   
CVector3::operator*(float scalar)
{
    return CVector3(scalar*x, scalar*y, scalar*z);

}   // End of operator*()


//-------------------------------------------------------------------------------
// @ operator*()
//-------------------------------------------------------------------------------
// Scalar multiplication
//-------------------------------------------------------------------------------
CVector3   
operator*(float scalar, const CVector3& vector)
{
    return CVector3(scalar*vector.x, scalar*vector.y, scalar*vector.z);

}   // End of operator*()


//-------------------------------------------------------------------------------
// @ CVector3::operator*()
//-------------------------------------------------------------------------------
// Scalar multiplication by self
//-------------------------------------------------------------------------------
CVector3&
CVector3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;

}   // End of CVector3::operator*=()


//-------------------------------------------------------------------------------
// @ operator/()
//-------------------------------------------------------------------------------
// Scalar division
//-------------------------------------------------------------------------------
CVector3   
CVector3::operator/(float scalar)
{
    return CVector3(x/scalar, y/scalar, z/scalar);

}   // End of operator/()


//-------------------------------------------------------------------------------
// @ CVector3::operator/=()
//-------------------------------------------------------------------------------
// Scalar division by self
//-------------------------------------------------------------------------------
CVector3&
CVector3::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;

}   // End of CVector3::operator/=()