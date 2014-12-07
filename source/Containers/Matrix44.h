#pragma once

//===============================================================================
// @ CMatrix44.h
// 
// Description
// ------------------------------------------------------------------------------
// Based on code from Essential Mathematics for Games
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//===============================================================================

#ifndef __CMatrix44__h__
#define __CMatrix44__h__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "Vector3.h"
#include "Vector4.h"

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class CMatrix33;
class CVector3;

class CMatrix44
{
public:
    // constructor/destructor
    inline CMatrix44() { Identity(); }
    inline ~CMatrix44() {}
    explicit CMatrix44( const CMatrix33& matrix );
    
    // copy operations
    CMatrix44(const CMatrix44& other);
    CMatrix44& operator=(const CMatrix44& other);

    // accessors
    float &operator()(unsigned int i, unsigned int j);
    float operator()(unsigned int i, unsigned int j) const;

    // comparison
    bool operator==( const CMatrix44& other ) const;
    bool operator!=( const CMatrix44& other ) const;
    bool IsZero() const;
    bool IsIdentity() const;

    // manipulators
    void SetRows( const CVector4& row1, const CVector4& row2, 
                  const CVector4& row3, const CVector4& row4 ); 
    void GetRows( CVector4& row1, CVector4& row2, CVector4& row3, CVector4& row4 ); 

    void SetColumns( const CVector4& col1, const CVector4& col2, 
                     const CVector4& col3, const CVector4& col4 ); 
    void GetColumns( CVector4& col1, CVector4& col2, CVector4& col3, CVector4& col4 ); 

    void Clean();
    void Identity();

    CMatrix44& AffineInverse();
    friend CMatrix44 AffineInverse( const CMatrix44& mat );

    CMatrix44& Transpose();
    friend CMatrix44 Transpose( const CMatrix44& mat );
        
    // transformations
    CMatrix44& Translation( const CVector3& xlate );
    CMatrix44& Rotation( const CMatrix33& matrix );
    CMatrix44& Rotation( float zRotation, float yRotation, float xRotation );
    CMatrix44& Rotation( const CVector3& axis, float angle );

    CMatrix44& Scaling( const CVector3& scale );

    CMatrix44& RotationX( float angle );
    CMatrix44& RotationY( float angle );
    CMatrix44& RotationZ( float angle );

    void GetFixedAngles( float& zRotation, float& yRotation, float& xRotation );
    void GetAxisAngle( CVector3& axis, float& angle );

    // operators

    // addition and subtraction
    CMatrix44 operator+( const CMatrix44& other ) const;
    CMatrix44& operator+=( const CMatrix44& other );
    CMatrix44 operator-( const CMatrix44& other ) const;
    CMatrix44& operator-=( const CMatrix44& other );

    CMatrix44 operator-() const;

    // multiplication
    CMatrix44& operator*=( const CMatrix44& matrix );
    CMatrix44 operator*( const CMatrix44& matrix ) const;

    // column vector multiplier
    CVector4 operator*( const CVector4& vector ) const;
    // row vector multiplier
    friend CVector4 operator*( const CVector4& vector, const CMatrix44& matrix );

    // scalar multiplication
    CMatrix44& operator*=( float scalar );
    friend CMatrix44 operator*( float scalar, const CMatrix44& matrix );
    CMatrix44 operator*( float scalar ) const;

    // vector3 ops
    CVector3 Transform( const CVector3& point ) const;

    // point ops
    CVector3 TransformPoint( const CVector3& point ) const;

	CVector3 TransformNormal( CVector3& point ) const;

    // low-level data accessors - implementation-dependent
    operator float*() { return mV; }
    operator const float*() const { return mV; }

    // member variables
    float mV[16];

protected:

private:
};

//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ CMatrix44::operator()()
//-------------------------------------------------------------------------------
// 2D array accessor
//-------------------------------------------------------------------------------
inline float&
CMatrix44::operator()(unsigned int i, unsigned int j)
{
   return mV[i + 4*j];

}   // End of CMatrix44::operator()()

//-------------------------------------------------------------------------------
// @ CMatrix44::operator()()
//-------------------------------------------------------------------------------
// 2D array accessor
//-------------------------------------------------------------------------------
inline float
CMatrix44::operator()(unsigned int i, unsigned int j) const
{
   return mV[i + 4*j];

}   // End of CMatrix44::operator()()

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

#endif
