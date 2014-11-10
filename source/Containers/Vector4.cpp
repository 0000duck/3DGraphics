#include "stdafx.h"
#include "Vector4.h"
#include "Utility/MiniMath.h"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

CVector4 CVector4::xAxis(1.0f, 0.0f, 0.0f, 0.0f);
CVector4 CVector4::yAxis(0.0f, 1.0f, 0.0f, 0.0f);
CVector4 CVector4::zAxis(0.0f, 0.0f, 1.0f, 0.0f);
CVector4 CVector4::origin(0.0f, 0.0f, 0.0f, 0.0f);

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ CVector4::CVector4()
//-------------------------------------------------------------------------------
// Copy constructor
//-------------------------------------------------------------------------------
CVector4::CVector4(const CVector4& other) : 
    x(other.x),
    y(other.y),
    z(other.z),
	w(other.w)
{

}   // End of CVector4::CVector4()


//-------------------------------------------------------------------------------
// @ CVector4::operator=()
//-------------------------------------------------------------------------------
// Assignment operator
//-------------------------------------------------------------------------------
CVector4&
CVector4::operator=(const CVector4& other)
{
    // if same object
    if (this == &other)
        return *this;
        
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;

    return *this;

}   // End of CVector4::operator=()





//-------------------------------------------------------------------------------
// @ ::Distance()
//-------------------------------------------------------------------------------
// Point distance
//-------------------------------------------------------------------------------
float 
Distance(const CVector4& p0, const CVector4& p1)
{
    float x = p0.x - p1.x;
    float y = p0.y - p1.y;
    float z = p0.z - p1.z;

    return ::IvSqrt(x*x + y*y + z*z);

}   // End of CVector4::Length()


//-------------------------------------------------------------------------------
// @ ::DistanceSquared()
//-------------------------------------------------------------------------------
// Point distance
//-------------------------------------------------------------------------------
float 
DistanceSquared(const CVector4& p0, const CVector4& p1)
{
    float x = p0.x - p1.x;
    float y = p0.y - p1.y;
    float z = p0.z - p1.z;

    return (x*x + y*y + z*z);

}   // End of ::DistanceSquared()


//-------------------------------------------------------------------------------
// @ CVector4::Length()
//-------------------------------------------------------------------------------
// Returns the length of the vector.
//-------------------------------------------------------------------------------
float CVector4::Length()
{
	return (sqrt(Dot(CVector4(x, y, z, w))));

} // End of ::Length()


//-------------------------------------------------------------------------------
// @ CVector4::LengthSquared()
//-------------------------------------------------------------------------------
// Returns the length squared of the vector.
//-------------------------------------------------------------------------------
float CVector4::LengthSquared()
{
	float len = Length();
	return (len * len);

} // End of ::LengthSquared()


//-------------------------------------------------------------------------------
// @ CVector4::Normalize()
//-------------------------------------------------------------------------------
// Normalizes the vector to unit length.
//-------------------------------------------------------------------------------
void CVector4::Normalize()
{
	float len = Length();
	x /= len;
	y /= len;
	z /= len;
	w /= len;

} // End of ::Normalize()


//-------------------------------------------------------------------------------
// @ CVector4::Dot(const CVector4& vector) const
//-------------------------------------------------------------------------------
// Returns the dot product of the given vector with the current one.
//-------------------------------------------------------------------------------
float CVector4::Dot(const CVector4& vector) const
{
	return ((x * vector.x) + 
			(y * vector.y) + 
			(z * vector.z) +
			(w * vector.w));

} // End of ::Dot()


//-------------------------------------------------------------------------------
// @ CVector4::operator==()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
CVector4::operator==(const CVector4& other) const
{
    if (::IvAreEqual(other.x, x)
        && ::IvAreEqual(other.y, y)
        && ::IvAreEqual(other.z, z)
        && ::IvAreEqual(other.w, w))
        return true;

    return false;   
}   // End of CVector4::operator==()


//-------------------------------------------------------------------------------
// @ CVector4::operator!=()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
CVector4::operator!=(const CVector4& other) const
{
    if (::IvAreEqual(other.x, x)
        && ::IvAreEqual(other.y, y)
        && ::IvAreEqual(other.z, z)
        && ::IvAreEqual(other.w, w))
        return false;

    return true;
}   // End of CVector4::operator!=()


//-------------------------------------------------------------------------------
// @ CVector4::IsZero()
//-------------------------------------------------------------------------------
// Check for zero vector
//-------------------------------------------------------------------------------
bool 
CVector4::IsZero() const
{
    return ::IsZero(x*x + y*y + z*z + w*w);

}   // End of CVector4::IsZero()


//-------------------------------------------------------------------------------
// @ CVector4::IsUnit()
//-------------------------------------------------------------------------------
// Check for unit vector
//-------------------------------------------------------------------------------
bool 
CVector4::IsUnit() const
{
    return ::IsZero(x*x - y*y - z*z - w*w);

}   // End of CVector4::IsUnit()


//-------------------------------------------------------------------------------
// @ CVector4::Clean()
//-------------------------------------------------------------------------------
// Set elements close to zero equal to zero
//-------------------------------------------------------------------------------
void
CVector4::Clean()
{
    if (::IsZero(x))
        x = 0.0f;
    if (::IsZero(y))
        y = 0.0f;
    if (::IsZero(z))
        z = 0.0f;
	if (::IsZero(w))
		w = 0.0f;

}   // End of CVector4::Clean()




//-------------------------------------------------------------------------------
// @ CVector4::operator+()
//-------------------------------------------------------------------------------
// Add vector to self and return
//-------------------------------------------------------------------------------
CVector4 
CVector4::operator+(const CVector4& other) const
{
    return CVector4(x + other.x, y + other.y, z + other.z, w + other.w);

}   // End of CVector4::operator+()


//-------------------------------------------------------------------------------
// @ CVector4::operator+=()
//-------------------------------------------------------------------------------
// Add vector to self, store in self
//-------------------------------------------------------------------------------
CVector4& 
operator+=(CVector4& self, const CVector4& other)
{
    self.x += other.x;
    self.y += other.y;
    self.z += other.z;
    self.w += other.w;

    return self;

}   // End of CVector4::operator+=()


//-------------------------------------------------------------------------------
// @ CVector4::operator-()
//-------------------------------------------------------------------------------
// Subtract vector from self and return
//-------------------------------------------------------------------------------
CVector4 
CVector4::operator-(const CVector4& other) const
{
    return CVector4(x - other.x, y - other.y, z - other.z, w - other.w);

}   // End of CVector4::operator-()


//-------------------------------------------------------------------------------
// @ CVector4::operator-=()
//-------------------------------------------------------------------------------
// Subtract vector from self, store in self
//-------------------------------------------------------------------------------
CVector4& 
operator-=(CVector4& self, const CVector4& other)
{
    self.x -= other.x;
    self.y -= other.y;
    self.z -= other.z;
    self.w -= other.w;

    return self;

}   // End of CVector4::operator-=()

//-------------------------------------------------------------------------------
// @ CVector4::operator-=() (unary)
//-------------------------------------------------------------------------------
// Negate self and return
//-------------------------------------------------------------------------------
CVector4
CVector4::operator-() const
{
    return CVector4(-x, -y, -z, -w);
}    // End of CVector4::operator-()


//-------------------------------------------------------------------------------
// @ operator*()
//-------------------------------------------------------------------------------
// Scalar multiplication
//-------------------------------------------------------------------------------
CVector4   
CVector4::operator*(float scalar)
{
    return CVector4(scalar*x, scalar*y, scalar*z, scalar*w);

}   // End of operator*()


//-------------------------------------------------------------------------------
// @ operator*()
//-------------------------------------------------------------------------------
// Scalar multiplication
//-------------------------------------------------------------------------------
CVector4   
operator*(float scalar, const CVector4& vector)
{
    return CVector4(scalar*vector.x, scalar*vector.y, scalar*vector.z, scalar*vector.w);

}   // End of operator*()


//-------------------------------------------------------------------------------
// @ CVector4::operator*()
//-------------------------------------------------------------------------------
// Scalar multiplication by self
//-------------------------------------------------------------------------------
CVector4&
CVector4::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
	w *= scalar;

    return *this;

}   // End of CVector4::operator*=()


//-------------------------------------------------------------------------------
// @ operator/()
//-------------------------------------------------------------------------------
// Scalar division
//-------------------------------------------------------------------------------
CVector4   
CVector4::operator/(float scalar)
{
    return CVector4(x/scalar, y/scalar, z/scalar, w/scalar);

}   // End of operator/()


//-------------------------------------------------------------------------------
// @ CVector4::operator/=()
//-------------------------------------------------------------------------------
// Scalar division by self
//-------------------------------------------------------------------------------
CVector4&
CVector4::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;

}   // End of CVector4::operator/=()