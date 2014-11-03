//===============================================================================
// @ CMatrix33.cpp
// 
// 3x3 matrix class
// ------------------------------------------------------------------------------
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "StdAfx.h"
#include <iostream>
#include "Matrix33.h"
#include "MiniMath.h"
#include "Quat.h"
#include "Vector3.h"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ CMatrix33::CMatrix33()
//-------------------------------------------------------------------------------
// Axis-angle constructor
//-------------------------------------------------------------------------------
CMatrix33::CMatrix33( const CQuat& quat )
{
    (void) Rotation( quat );

}   // End of CMatrix33::CMatrix33()


//-------------------------------------------------------------------------------
// @ CMatrix33::CMatrix33()
//-------------------------------------------------------------------------------
// Copy constructor
//-------------------------------------------------------------------------------
CMatrix33::CMatrix33(const CMatrix33& other)
{
    mV[0] = other.mV[0];
    mV[1] = other.mV[1];
    mV[2] = other.mV[2];
    mV[3] = other.mV[3];
    mV[4] = other.mV[4];
    mV[5] = other.mV[5];
    mV[6] = other.mV[6];
    mV[7] = other.mV[7];
    mV[8] = other.mV[8];

}   // End of CMatrix33::CMatrix33()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator=()
//-------------------------------------------------------------------------------
// Assignment operator
//-------------------------------------------------------------------------------
CMatrix33&
CMatrix33::operator=(const CMatrix33& other)
{
    // if same object
    if ( this == &other )
        return *this;
        
    mV[0] = other.mV[0];
    mV[1] = other.mV[1];
    mV[2] = other.mV[2];
    mV[3] = other.mV[3];
    mV[4] = other.mV[4];
    mV[5] = other.mV[5];
    mV[6] = other.mV[6];
    mV[7] = other.mV[7];
    mV[8] = other.mV[8];
    
    return *this;

}   // End of CMatrix33::operator=()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator==()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
CMatrix33::operator==( const CMatrix33& other ) const
{
    for (unsigned int i = 0; i < 9; ++i)
    {
        if ( !IvAreEqual(mV[i], other.mV[i]) )
            return false;
    }
    return true;

}   // End of CMatrix33::operator==()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator!=()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
CMatrix33::operator!=( const CMatrix33& other ) const
{
    for (unsigned int i = 0; i < 9; ++i)
    {
        if ( !IvAreEqual(mV[i], other.mV[i]) )
            return true;
    }
    return false;

}   // End of CMatrix33::operator!=()


//-------------------------------------------------------------------------------
// @ CMatrix33::IsZero()
//-------------------------------------------------------------------------------
// Check for zero matrix
//-------------------------------------------------------------------------------
bool 
CMatrix33::IsZero() const
{
    for (unsigned int i = 0; i < 9; ++i)
    {
        if ( !::IsZero( mV[i] ) )
            return false;
    }
    return true;

}   // End of CMatrix33::IsZero()


//-------------------------------------------------------------------------------
// @ CMatrix33::IsIdentity()
//-------------------------------------------------------------------------------
// Check for identity matrix
//-------------------------------------------------------------------------------
bool 
CMatrix33::IsIdentity() const
{
    return ::IvAreEqual( 1.0f, mV[0] )
        && ::IvAreEqual( 1.0f, mV[4] )
        && ::IvAreEqual( 1.0f, mV[8] )
        && ::IsZero( mV[1] ) 
        && ::IsZero( mV[2] )
        && ::IsZero( mV[3] )
        && ::IsZero( mV[5] ) 
        && ::IsZero( mV[6] )
        && ::IsZero( mV[7] );

}   // End of CMatrix33::IsIdentity()


//-------------------------------------------------------------------------------
// @ CMatrix33::SetRows()
//-------------------------------------------------------------------------------
// Set matrix, row by row
//-------------------------------------------------------------------------------
void 
CMatrix33::SetRows( const CVector3& row1, const CVector3& row2, const CVector3& row3 )
{
    mV[0] = row1.x;
    mV[3] = row1.y;
    mV[6] = row1.z;

    mV[1] = row2.x;
    mV[4] = row2.y;
    mV[7] = row2.z;

    mV[2] = row3.x;
    mV[5] = row3.y;
    mV[8] = row3.z;

}   // End of CMatrix33::SetRows()


//-------------------------------------------------------------------------------
// @ CMatrix33::GetRows()
//-------------------------------------------------------------------------------
// Get matrix, row by row
//-------------------------------------------------------------------------------
void 
CMatrix33::GetRows( CVector3& row1, CVector3& row2, CVector3& row3 ) const
{
    row1.x = mV[0];
    row1.y = mV[3];
    row1.z = mV[6];

    row2.x = mV[1];
    row2.y = mV[4];
    row2.z = mV[7];

    row3.x = mV[2];
    row3.y = mV[5];
    row3.z = mV[8];
}   // End of CMatrix33::GetRows()


//-------------------------------------------------------------------------------
// @ CMatrix33::GetRow()
//-------------------------------------------------------------------------------
// Get matrix, row by row
//-------------------------------------------------------------------------------
CVector3 
CMatrix33::GetRow( unsigned int i ) const
{
    ASSERT( i < 3 );
    return CVector3( mV[i], mV[i+3], mV[i+6] );

}   // End of CMatrix33::GetRow()


//-------------------------------------------------------------------------------
// @ CMatrix33::SetColumns()
//-------------------------------------------------------------------------------
// Set matrix, row by row
//-------------------------------------------------------------------------------
void 
CMatrix33::SetColumns( const CVector3& col1, const CVector3& col2, const CVector3& col3 )
{
    mV[0] = col1.x;
    mV[1] = col1.y;
    mV[2] = col1.z;

    mV[3] = col2.x;
    mV[4] = col2.y;
    mV[5] = col2.z;

    mV[6] = col3.x;
    mV[7] = col3.y;
    mV[8] = col3.z;

}   // End of CMatrix33::SetColumns()


//-------------------------------------------------------------------------------
// @ CMatrix33::GetColumns()
//-------------------------------------------------------------------------------
// Get matrix, row by row
//-------------------------------------------------------------------------------
void 
CMatrix33::GetColumns( CVector3& col1, CVector3& col2, CVector3& col3 ) const
{
    col1.x = mV[0];
    col1.y = mV[1];
    col1.z = mV[2];

    col2.x = mV[3];
    col2.y = mV[4];
    col2.z = mV[5];

    col3.x = mV[6];
    col3.y = mV[7];
    col3.z = mV[8];

}   // End of CMatrix33::GetColumns()


//-------------------------------------------------------------------------------
// @ CMatrix33::GetColumns()
//-------------------------------------------------------------------------------
// Get matrix, row by row
//-------------------------------------------------------------------------------
CVector3 
CMatrix33::GetColumn( unsigned int i ) const 
{
    ASSERT( i < 3 );
    return CVector3( mV[3*i], mV[3*i+1], mV[3*i+2] );

}   // End of CMatrix33::GetColumns()


//-------------------------------------------------------------------------------
// @ CMatrix33::Clean()
//-------------------------------------------------------------------------------
// Set elements close to zero equal to zero
//-------------------------------------------------------------------------------
void
CMatrix33::Clean()
{
    for (unsigned int i = 0; i < 9; ++i)
    {
        if ( ::IsZero( mV[i] ) )
            mV[i] = 0.0f;
    }

}   // End of CMatrix33::Clean()


//-------------------------------------------------------------------------------
// @ CMatrix33::Identity()
//-------------------------------------------------------------------------------
// Set to identity matrix
//-------------------------------------------------------------------------------
void
CMatrix33::Identity()
{
    mV[0] = 1.0f;
    mV[1] = 0.0f;
    mV[2] = 0.0f;
    mV[3] = 0.0f;
    mV[4] = 1.0f;
    mV[5] = 0.0f;
    mV[6] = 0.0f;
    mV[7] = 0.0f;
    mV[8] = 1.0f;

}   // End of CMatrix33::Identity()


//-------------------------------------------------------------------------------
// @ CMatrix33::Inverse()
//-------------------------------------------------------------------------------
// Set self to inverse
//-------------------------------------------------------------------------------
CMatrix33& 
CMatrix33::Inverse()
{
    *this = ::Inverse(*this);

    return *this;

}   // End of CMatrix33::Inverse()


//-------------------------------------------------------------------------------
// @ CMatrix33::Inverse()
//-------------------------------------------------------------------------------
// Compute matrix inverse
//-------------------------------------------------------------------------------
CMatrix33 
Inverse( const CMatrix33& mat )
{
    CMatrix33 result;
    
    // compute determinant
    float cofactor0 = mat.mV[4]*mat.mV[8] - mat.mV[5]*mat.mV[7];
    float cofactor3 = mat.mV[2]*mat.mV[7] - mat.mV[1]*mat.mV[8];
    float cofactor6 = mat.mV[1]*mat.mV[5] - mat.mV[2]*mat.mV[4];
    float det = mat.mV[0]*cofactor0 + mat.mV[3]*cofactor3 + mat.mV[6]*cofactor6;
    if (::IsZero( det ))
    {
        ASSERT( false );
		std::cerr << "Matrix33::Inverse() -- singular matrix\n";
        return result;
    }

    // create adjoint matrix and multiply by 1/det to get inverse
    float invDet = 1.0f/det;
    result.mV[0] = invDet*cofactor0;
    result.mV[1] = invDet*cofactor3;
    result.mV[2] = invDet*cofactor6;
   
    result.mV[3] = invDet*(mat.mV[5]*mat.mV[6] - mat.mV[3]*mat.mV[8]);
    result.mV[4] = invDet*(mat.mV[0]*mat.mV[8] - mat.mV[2]*mat.mV[6]);
    result.mV[5] = invDet*(mat.mV[2]*mat.mV[3] - mat.mV[0]*mat.mV[5]);

    result.mV[6] = invDet*(mat.mV[3]*mat.mV[7] - mat.mV[4]*mat.mV[6]);
    result.mV[7] = invDet*(mat.mV[1]*mat.mV[6] - mat.mV[0]*mat.mV[7]);
    result.mV[8] = invDet*(mat.mV[0]*mat.mV[4] - mat.mV[1]*mat.mV[3]);

    return result;

}   // End of CMatrix33::Inverse()


//-------------------------------------------------------------------------------
// @ CMatrix33::Transpose()
//-------------------------------------------------------------------------------
// Set self to transpose
//-------------------------------------------------------------------------------
CMatrix33& 
CMatrix33::Transpose()
{
    float temp = mV[1];
    mV[1] = mV[3];
    mV[3] = temp;

    temp = mV[2];
    mV[2] = mV[6];
    mV[6] = temp;

    temp = mV[5];
    mV[5] = mV[7];
    mV[7] = temp;

    return *this;

}   // End of CMatrix33::Transpose()


//-------------------------------------------------------------------------------
// @ CMatrix33::Transpose()
//-------------------------------------------------------------------------------
// Compute matrix transpose
//-------------------------------------------------------------------------------
CMatrix33 
Transpose( const CMatrix33& mat )
{
    CMatrix33 result;

    result.mV[0] = mat.mV[0];
    result.mV[1] = mat.mV[3];
    result.mV[2] = mat.mV[6];
    result.mV[3] = mat.mV[1];
    result.mV[4] = mat.mV[4];
    result.mV[5] = mat.mV[7];
    result.mV[6] = mat.mV[2];
    result.mV[7] = mat.mV[5];
    result.mV[8] = mat.mV[8];

    return result;

}   // End of CMatrix33::Transpose()


//-------------------------------------------------------------------------------
// @ CMatrix33::Determinant()
//-------------------------------------------------------------------------------
// Get determinant of matrix
//-------------------------------------------------------------------------------
float 
CMatrix33::Determinant() const
{
    return mV[0]*(mV[4]*mV[8] - mV[5]*mV[7]) 
         + mV[3]*(mV[2]*mV[7] - mV[1]*mV[8])
         + mV[6]*(mV[1]*mV[5] - mV[2]*mV[4]);

}   // End of CMatrix33::Determinant()


//-------------------------------------------------------------------------------
// @ CMatrix33::Adjoint()
//-------------------------------------------------------------------------------
// Compute matrix adjoint
//-------------------------------------------------------------------------------
CMatrix33 
CMatrix33::Adjoint() const
{
    CMatrix33 result;
    
    // compute transpose of cofactors
    result.mV[0] = mV[4]*mV[8] - mV[5]*mV[7];
    result.mV[1] = mV[2]*mV[7] - mV[1]*mV[8];
    result.mV[2] = mV[1]*mV[5] - mV[2]*mV[4];
   
    result.mV[3] = mV[5]*mV[6] - mV[3]*mV[8];
    result.mV[4] = mV[0]*mV[8] - mV[2]*mV[6];
    result.mV[5] = mV[2]*mV[3] - mV[0]*mV[5];

    result.mV[6] = mV[3]*mV[7] - mV[4]*mV[6];
    result.mV[7] = mV[1]*mV[6] - mV[0]*mV[7];
    result.mV[8] = mV[0]*mV[4] - mV[1]*mV[3];

    return result;

}   // End of CMatrix33::Adjoint()


//-------------------------------------------------------------------------------
// @ CMatrix33::Trace()
//-------------------------------------------------------------------------------
// Get trace of matrix
//-------------------------------------------------------------------------------
float 
CMatrix33::Trace() const
{
    return mV[0] + mV[4] + mV[8];

}   // End of CMatrix33::Trace()


//-------------------------------------------------------------------------------
// @ CMatrix33::Rotation()
//-------------------------------------------------------------------------------
// Set as rotation matrix based on quaternion
//-------------------------------------------------------------------------------
CMatrix33& 
CMatrix33::Rotation( const CQuat& rotate )
{
    ASSERT( rotate.IsUnit() );

    float xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

    xs = rotate.x+rotate.x;   
    ys = rotate.y+rotate.y;
    zs = rotate.z+rotate.z;
    wx = rotate.w*xs;
    wy = rotate.w*ys;
    wz = rotate.w*zs;
    xx = rotate.x*xs;
    xy = rotate.x*ys;
    xz = rotate.x*zs;
    yy = rotate.y*ys;
    yz = rotate.y*zs;
    zz = rotate.z*zs;

    mV[0] = 1.0f - (yy + zz);
    mV[3] = xy - wz;
    mV[6] = xz + wy;
    
    mV[1] = xy + wz;
    mV[4] = 1.0f - (xx + zz);
    mV[7] = yz - wx;
    
    mV[2] = xz - wy;
    mV[5] = yz + wx;
    mV[8] = 1.0f - (xx + yy);

    return *this;

}   // End of Rotation()


//----------------------------------------------------------------------------
// @ CMatrix33::Rotation()
// ---------------------------------------------------------------------------
// Sets the matrix to a rotation matrix (by Euler angles).
//----------------------------------------------------------------------------
CMatrix33 &
CMatrix33::Rotation( float zRotation, float yRotation, float xRotation )
{
    // This is an "unrolled" contatenation of rotation matrices X Y & Z
    float Cx, Sx;
    IvSinCos(xRotation, Sx, Cx);

    float Cy, Sy;
    IvSinCos(yRotation, Sy, Cy);

    float Cz, Sz;
    IvSinCos(zRotation, Sz, Cz);

    mV[0] =  (Cy * Cz);
    mV[3] = -(Cy * Sz);  
    mV[6] =  Sy;

    mV[1] =  (Sx * Sy * Cz) + (Cx * Sz);
    mV[4] = -(Sx * Sy * Sz) + (Cx * Cz);
    mV[7] = -(Sx * Cy); 

    mV[2] = -(Cx * Sy * Cz) + (Sx * Sz);
    mV[5] =  (Cx * Sy * Sz) + (Sx * Cz);
    mV[8] =  (Cx * Cy);

    return *this;

}  // End of CMatrix33::Rotation()


//----------------------------------------------------------------------------
// @ CMatrix33::Rotation()
// ---------------------------------------------------------------------------
// Sets the matrix to a rotation matrix (by axis and angle).
//----------------------------------------------------------------------------
CMatrix33 &
CMatrix33::Rotation( const CVector3& axis, float angle )
{
    float c, s;
    IvSinCos(angle, s, c);
    float t = 1.0f - c;

    CVector3 nAxis = axis;
    nAxis.Normalize();

    // intermediate values
    float tx = t*nAxis.x;  float ty = t*nAxis.y;  float tz = t*nAxis.z;
    float sx = s*nAxis.x;  float sy = s*nAxis.y;  float sz = s*nAxis.z;
    float txy = tx*nAxis.y; float tyz = tx*nAxis.z; float txz = tx*nAxis.z;

    // set matrix
    mV[0] = tx*nAxis.x + c;
    mV[3] = txy - sz;
    mV[6] = txz + sy;
    mV[1] = txy + sz;
    mV[4] = ty*nAxis.y + c;
    mV[7] = tyz - sx;
    mV[2] = txz - sy;
    mV[5] = tyz + sx;
    mV[8] = tz*nAxis.z + c;

    return *this;

}  // End of CMatrix33::Rotation()


//-------------------------------------------------------------------------------
// @ CMatrix33::Scaling()
//-------------------------------------------------------------------------------
// Set as scaling matrix based on vector
//-------------------------------------------------------------------------------
CMatrix33& 
CMatrix33::Scaling( const CVector3& scaleFactors )
{
    mV[0] = scaleFactors.x;
    mV[1] = 0.0f;
    mV[2] = 0.0f;
    mV[3] = 0.0f;
    mV[4] = scaleFactors.y;
    mV[5] = 0.0f;
    mV[6] = 0.0f;
    mV[7] = 0.0f;
    mV[8] = scaleFactors.z;

    return *this;

}   // End of Scaling()


//-------------------------------------------------------------------------------
// @ CMatrix33::RotationX()
//-------------------------------------------------------------------------------
// Set as rotation matrix, rotating by 'angle' radians around x-axis
//-------------------------------------------------------------------------------
CMatrix33& 
CMatrix33::RotationX( float angle )
{
    float sintheta, costheta;
    IvSinCos(angle, sintheta, costheta);

    mV[0] = 1.0f;
    mV[1] = 0.0f;
    mV[2] = 0.0f;
    mV[3] = 0.0f;
    mV[4] = costheta;
    mV[5] = sintheta;
    mV[6] = 0.0f;
    mV[7] = -sintheta;
    mV[8] = costheta;

    return *this;

}   // End of RotationX()


//-------------------------------------------------------------------------------
// @ CMatrix33::RotationY()
//-------------------------------------------------------------------------------
// Set as rotation matrix, rotating by 'angle' radians around y-axis
//-------------------------------------------------------------------------------
CMatrix33& 
CMatrix33::RotationY( float angle )
{
    float sintheta, costheta;
    IvSinCos(angle, sintheta, costheta);

    mV[0] = costheta;
    mV[1] = 0.0f;
    mV[2] = -sintheta;
    mV[3] = 0.0f;
    mV[4] = 1.0f;
    mV[5] = 0.0f;
    mV[6] = sintheta;
    mV[7] = 0.0f;
    mV[8] = costheta;

    return *this;

}   // End of RotationY()


//-------------------------------------------------------------------------------
// @ CMatrix33::RotationZ()
//-------------------------------------------------------------------------------
// Set as rotation matrix, rotating by 'angle' radians around z-axis
//-------------------------------------------------------------------------------
CMatrix33& 
CMatrix33::RotationZ( float angle )
{
    float sintheta, costheta;
    IvSinCos(angle, sintheta, costheta);

    mV[0] = costheta;
    mV[1] = sintheta;
    mV[2] = 0.0f;
    mV[3] = -sintheta;
    mV[4] = costheta;
    mV[5] = 0.0f;
    mV[6] = 0.0f;
    mV[7] = 0.0f;
    mV[8] = 1.0f;

    return *this;

}   // End of RotationZ()


//----------------------------------------------------------------------------
// @ CMatrix33::GetFixedAngles()
// ---------------------------------------------------------------------------
// Gets one set of possible z-y-x fixed angles that will generate this matrix
// Assumes that this is a rotation matrix
//----------------------------------------------------------------------------
void
CMatrix33::GetFixedAngles( float& zRotation, float& yRotation, float& xRotation )
{
    float Cx, Sx;
    float Cy, Sy;
    float Cz, Sz;

    Sy = mV[6];
    Cy = ::IvSqrt( 1.0f - Sy*Sy );
    // normal case
    if ( !::IsZero( Cy ) )
    {
        float factor = 1.0f/Cy;
        Sx = -mV[7]*factor;
        Cx = mV[8]*factor;
        Sz = -mV[3]*factor;
        Cz = mV[0]*factor;
    }
    // x and z axes aligned
    else
    {
        Sz = 0.0f;
        Cz = 1.0f;
        Sx = mV[5];
        Cx = mV[4];
    }

    zRotation = atan2f( Sz, Cz );
    yRotation = atan2f( Sy, Cy );
    xRotation = atan2f( Sx, Cx );

}  // End of CMatrix33::GetFixedAngles()


//----------------------------------------------------------------------------
// @ CMatrix33::GetAxisAngle()
// ---------------------------------------------------------------------------
// Gets one possible axis-angle pair that will generate this matrix
// Assumes that this is a rotation matrix
//----------------------------------------------------------------------------
void
CMatrix33::GetAxisAngle( CVector3& axis, float& angle )
{
    float trace = mV[0] + mV[4] + mV[8];
    float cosTheta = 0.5f*(trace - 1.0f);
    angle = acosf( cosTheta );

    // angle is zero, axis can be anything
    if ( ::IsZero( angle ) )
    {
        axis = CVector3::xAxis;
    }
    // standard case
    else if ( angle < kPI-kEpsilon )
    {
        axis.Set( mV[5]-mV[7], mV[6]-mV[2], mV[1]-mV[3] );
        axis.Normalize();
    }
    // angle is 180 degrees
    else
    {
        unsigned int i = 0;
        if ( mV[4] > mV[0] )
            i = 1;
        if ( mV[8] > mV[i + 3*i] )
            i = 2;
        unsigned int j = (i+1)%3;
        unsigned int k = (j+1)%3;
        float s = ::IvSqrt( mV[i + 3*i] - mV[j + 3*j] - mV[k + 3*k] + 1.0f );
        axis[i] = 0.5f*s;
        float recip = 0.5f/s;
        axis[j] = (mV[i + 3*j])*recip;
        axis[k] = (mV[k + 3*i])*recip;
    }

}  // End of CMatrix33::GetAxisAngle()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator+()
//-------------------------------------------------------------------------------
// Matrix addition 
//-------------------------------------------------------------------------------
CMatrix33
CMatrix33::operator+( const CMatrix33& other ) const
{
    CMatrix33 result;

    for (unsigned int i = 0; i < 9; ++i)
    {
        result.mV[i] = mV[i] + other.mV[i];
    }

    return result;

}   // End of CMatrix33::operator-()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator+=()
//-------------------------------------------------------------------------------
// Matrix addition by self
//-------------------------------------------------------------------------------
CMatrix33&
CMatrix33::operator+=( const CMatrix33& other )
{
    for (unsigned int i = 0; i < 9; ++i)
    {
        mV[i] += other.mV[i];
    }

    return *this;

}   // End of CMatrix33::operator+=()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator-()
//-------------------------------------------------------------------------------
// Matrix subtraction 
//-------------------------------------------------------------------------------
CMatrix33
CMatrix33::operator-( const CMatrix33& other ) const
{
    CMatrix33 result;

    for (unsigned int i = 0; i < 9; ++i)
    {
        result.mV[i] = mV[i] - other.mV[i];
    }

    return result;

}   // End of CMatrix33::operator-()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator-=()
//-------------------------------------------------------------------------------
// Matrix subtraction by self
//-------------------------------------------------------------------------------
CMatrix33&
CMatrix33::operator-=( const CMatrix33& other )
{
    for (unsigned int i = 0; i < 9; ++i)
    {
        mV[i] -= other.mV[i];
    }

    return *this;

}   // End of CMatrix33::operator-=()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator-=() (unary)
//-------------------------------------------------------------------------------
// Negate self and return
//-------------------------------------------------------------------------------
CMatrix33
CMatrix33::operator-() const
{
    CMatrix33 result;

    for (unsigned int i = 0; i < 16; ++i)
    {
        result.mV[i] = -mV[i];
    }

    return result;

}    // End of CQuat::operator-()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator*()
//-------------------------------------------------------------------------------
// Matrix multiplication
//-------------------------------------------------------------------------------
CMatrix33  
CMatrix33::operator*( const CMatrix33& other ) const
{
    CMatrix33 result;

    result.mV[0] = mV[0]*other.mV[0] + mV[3]*other.mV[1] + mV[6]*other.mV[2];
    result.mV[1] = mV[1]*other.mV[0] + mV[4]*other.mV[1] + mV[7]*other.mV[2];
    result.mV[2] = mV[2]*other.mV[0] + mV[5]*other.mV[1] + mV[8]*other.mV[2];
    result.mV[3] = mV[0]*other.mV[3] + mV[3]*other.mV[4] + mV[6]*other.mV[5];
    result.mV[4] = mV[1]*other.mV[3] + mV[4]*other.mV[4] + mV[7]*other.mV[5];
    result.mV[5] = mV[2]*other.mV[3] + mV[5]*other.mV[4] + mV[8]*other.mV[5];
    result.mV[6] = mV[0]*other.mV[6] + mV[3]*other.mV[7] + mV[6]*other.mV[8];
    result.mV[7] = mV[1]*other.mV[6] + mV[4]*other.mV[7] + mV[7]*other.mV[8];
    result.mV[8] = mV[2]*other.mV[6] + mV[5]*other.mV[7] + mV[8]*other.mV[8];

    return result;

}   // End of CMatrix33::operator*()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator*=()
//-------------------------------------------------------------------------------
// Matrix multiplication by self
//-------------------------------------------------------------------------------
CMatrix33&
CMatrix33::operator*=( const CMatrix33& other )
{
    CMatrix33 result;

    result.mV[0] = mV[0]*other.mV[0] + mV[3]*other.mV[1] + mV[6]*other.mV[2];
    result.mV[1] = mV[1]*other.mV[0] + mV[4]*other.mV[1] + mV[7]*other.mV[2];
    result.mV[2] = mV[2]*other.mV[0] + mV[5]*other.mV[1] + mV[8]*other.mV[2];
    result.mV[3] = mV[0]*other.mV[3] + mV[3]*other.mV[4] + mV[6]*other.mV[5];
    result.mV[4] = mV[1]*other.mV[3] + mV[4]*other.mV[4] + mV[7]*other.mV[5];
    result.mV[5] = mV[2]*other.mV[3] + mV[5]*other.mV[4] + mV[8]*other.mV[5];
    result.mV[6] = mV[0]*other.mV[6] + mV[3]*other.mV[7] + mV[6]*other.mV[8];
    result.mV[7] = mV[1]*other.mV[6] + mV[4]*other.mV[7] + mV[7]*other.mV[8];
    result.mV[8] = mV[2]*other.mV[6] + mV[5]*other.mV[7] + mV[8]*other.mV[8];

    for (unsigned int i = 0; i < 9; ++i)
    {
        mV[i] = result.mV[i];
    }

    return *this;

}   // End of CMatrix33::operator*=()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator*()
//-------------------------------------------------------------------------------
// Matrix-column vector multiplication
//-------------------------------------------------------------------------------
CVector3   
CMatrix33::operator*( const CVector3& other ) const
{
    CVector3 result;

    result.x = mV[0]*other.x + mV[3]*other.y + mV[6]*other.z;
    result.y = mV[1]*other.x + mV[4]*other.y + mV[7]*other.z;
    result.z = mV[2]*other.x + mV[5]*other.y + mV[8]*other.z;

    return result;

}   // End of CMatrix33::operator*()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator*()
//-------------------------------------------------------------------------------
// Row vector-matrix multiplication
//-------------------------------------------------------------------------------
CVector3   
operator*( const CVector3& vector, const CMatrix33& mat )
{
    CVector3 result;

    result.x = mat.mV[0]*vector.x + mat.mV[1]*vector.y + mat.mV[2]*vector.z;
    result.y = mat.mV[3]*vector.x + mat.mV[4]*vector.y + mat.mV[5]*vector.z;
    result.z = mat.mV[6]*vector.x + mat.mV[7]*vector.y + mat.mV[8]*vector.z;

    return result;

}   // End of CMatrix33::operator*()


//-------------------------------------------------------------------------------
// @ CMatrix33::*=()
//-------------------------------------------------------------------------------
// Matrix-scalar multiplication
//-------------------------------------------------------------------------------
CMatrix33& CMatrix33::operator*=( float scalar )
{
    mV[0] *= scalar;
    mV[1] *= scalar;
    mV[2] *= scalar;
    mV[3] *= scalar;
    mV[4] *= scalar;
    mV[5] *= scalar;
    mV[6] *= scalar;
    mV[7] *= scalar;
    mV[8] *= scalar;

    return *this;
}  // End of CMatrix33::operator*=()


//-------------------------------------------------------------------------------
// @ friend CMatrix33 *()
//-------------------------------------------------------------------------------
// Matrix-scalar multiplication
//-------------------------------------------------------------------------------
CMatrix33 operator*( float scalar, const CMatrix33& matrix )
{
    CMatrix33 result;
    result.mV[0] = matrix.mV[0] * scalar;
    result.mV[1] = matrix.mV[1] * scalar;
    result.mV[2] = matrix.mV[2] * scalar;
    result.mV[3] = matrix.mV[3] * scalar;
    result.mV[4] = matrix.mV[4] * scalar;
    result.mV[5] = matrix.mV[5] * scalar;
    result.mV[6] = matrix.mV[6] * scalar;
    result.mV[7] = matrix.mV[7] * scalar;
    result.mV[8] = matrix.mV[8] * scalar;

    return result;
}  // End of friend CMatrix33 operator*()


//-------------------------------------------------------------------------------
// @ CMatrix33::*()
//-------------------------------------------------------------------------------
// Matrix-scalar multiplication
//-------------------------------------------------------------------------------
CMatrix33 CMatrix33::operator*( float scalar ) const
{
    CMatrix33 result;
    result.mV[0] = mV[0] * scalar;
    result.mV[1] = mV[1] * scalar;
    result.mV[2] = mV[2] * scalar;
    result.mV[3] = mV[3] * scalar;
    result.mV[4] = mV[4] * scalar;
    result.mV[5] = mV[5] * scalar;
    result.mV[6] = mV[6] * scalar;
    result.mV[7] = mV[7] * scalar;
    result.mV[8] = mV[8] * scalar;

    return result;
}  // End of CMatrix33::operator*=()


