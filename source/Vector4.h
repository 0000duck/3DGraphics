#pragma once

//===============================================================================
// @ CVector4.h
// 
// 4D vector class
// ------------------------------------------------------------------------------
// Based on code from Essential Mathematics for Games
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//===============================================================================

#ifndef __CVector4__h__
#define __CVector4__h__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class CVector4
{
public:
    // constructor/destructor
    inline CVector4() {}
    inline CVector4( float _x, float _y, float _z, float _w ) :
        x(_x), y(_y), z(_z), w(_w)
    {
    }
    inline ~CVector4() {}

    // copy operations
    CVector4(const CVector4& other);
    CVector4& operator=(const CVector4& other);

    // accessors
    inline float& operator[]( unsigned int i )         { return (&x)[i]; }
    inline float operator[]( unsigned int i ) const    { return (&x)[i]; }

    float Length();
    float LengthSquared();

    // comparison
    bool operator==( const CVector4& other ) const;
    bool operator!=( const CVector4& other ) const;
    bool IsZero() const;
    bool IsUnit() const;

    // manipulators
    inline void Set( float _x, float _y, float _z, float _w );
    void Clean();       // sets near-zero elements to 0
    inline void Zero(); // sets all elements to 0
    void Normalize();   // sets to unit vector

    // operators

    // addition/subtraction
    CVector4 operator+( const CVector4& other ) const;
    CVector4& operator+=( const CVector4& other );
    CVector4 operator-( const CVector4& other ) const;
    CVector4 operator-() const;
    CVector4& operator-=( const CVector4& other );

    // scalar multiplication
    CVector4    operator*( float scalar );
    friend CVector4    operator*( float scalar, const CVector4& vector );
    CVector4&          operator*=( float scalar );
    CVector4    operator/( float scalar );
    CVector4&          operator/=( float scalar );

    // dot product
    float              Dot( const CVector4& vector ) const;
    friend float       Dot( const CVector4& vector1, const CVector4& vector2 );

    // useful defaults
    static CVector4    xAxis;
    static CVector4    yAxis;
    static CVector4    zAxis;
    static CVector4    wAxis;
    static CVector4    origin;
        
    // member variables
    float x, y, z, w;

protected:

private:
};

//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ CVector4::Set()
//-------------------------------------------------------------------------------
// Set vector elements
//-------------------------------------------------------------------------------
inline void 
CVector4::Set( float _x, float _y, float _z, float _w )
{
    x = _x; y = _y; z = _z; w = _w;
}   // End of CVector4::Set()

//-------------------------------------------------------------------------------
// @ CVector4::Zero()
//-------------------------------------------------------------------------------
// Zero all elements
//-------------------------------------------------------------------------------
inline void 
CVector4::Zero()
{
    x = y = z = w = 0.0f;
}   // End of CVector4::Zero()

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

#endif
