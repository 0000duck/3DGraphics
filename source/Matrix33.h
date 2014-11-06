//===============================================================================
// @ CMatrix33.h
// 
// Description
// ------------------------------------------------------------------------------
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//
//
//
//===============================================================================

#ifndef __CMatrix33__h__
#define __CMatrix33__h__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//class CQuat;
class CVector3;

class CMatrix33
{
public:
    // constructor/destructor
    inline CMatrix33() {}
    inline ~CMatrix33() {}
    //explicit CMatrix33( const CQuat& quat );
    
    // copy operations
    CMatrix33(const CMatrix33& other);
    CMatrix33& operator=(const CMatrix33& other);

    // accessors
    inline float& operator()(unsigned int i, unsigned int j);
    inline float operator()(unsigned int i, unsigned int j) const;

    // comparison
    bool operator==( const CMatrix33& other ) const;
    bool operator!=( const CMatrix33& other ) const;
    bool IsZero() const;
    bool IsIdentity() const;

    // manipulators
    void SetRows( const CVector3& row1, const CVector3& row2, const CVector3& row3 ); 
    void GetRows( CVector3& row1, CVector3& row2, CVector3& row3 ) const; 
    CVector3 GetRow( unsigned int i ) const; 

    void SetColumns( const CVector3& col1, const CVector3& col2, const CVector3& col3 ); 
    void GetColumns( CVector3& col1, CVector3& col2, CVector3& col3 ) const; 
    CVector3 GetColumn( unsigned int i ) const; 

    void Clean();
    void Identity();

    CMatrix33& Inverse();
    friend CMatrix33 Inverse( const CMatrix33& mat );

    CMatrix33& Transpose();
    friend CMatrix33 Transpose( const CMatrix33& mat );

    // useful computations
    CMatrix33 Adjoint() const;
    float Determinant() const;
    float Trace() const;
        
    // transformations
    //CMatrix33& Rotation( const CQuat& rotate );
    CMatrix33& Rotation( float zRotation, float yRotation, float xRotation );
    CMatrix33& Rotation( const CVector3& axis, float angle );

    CMatrix33& Scaling( const CVector3& scale );

    CMatrix33& RotationX( float angle );
    CMatrix33& RotationY( float angle );
    CMatrix33& RotationZ( float angle );

    void GetFixedAngles( float& zRotation, float& yRotation, float& xRotation );
    void GetAxisAngle( CVector3& axis, float& angle );

    // operators

    // addition and subtraction
    CMatrix33 operator+( const CMatrix33& other ) const;
    CMatrix33& operator+=( const CMatrix33& other );
    CMatrix33 operator-( const CMatrix33& other ) const;
    CMatrix33& operator-=( const CMatrix33& other );

    CMatrix33 operator-() const;

    // multiplication
    CMatrix33& operator*=( const CMatrix33& matrix );
    CMatrix33 operator*( const CMatrix33& matrix ) const;

    // column vector multiplier
    CVector3 operator*( const CVector3& vector ) const;
    // row vector multiplier
    friend CVector3 operator*( const CVector3& vector, const CMatrix33& matrix );

    CMatrix33& operator*=( float scalar );
    friend CMatrix33 operator*( float scalar, const CMatrix33& matrix );
    CMatrix33 operator*( float scalar ) const;

    // low-level data accessors - implementation-dependent
    operator float*() { return mV; }
    operator const float*() const { return mV; }

    // member variables
    float mV[9];

protected:

private:
};

//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ CMatrix33::operator()()
//-------------------------------------------------------------------------------
// 2D array accessor
//-------------------------------------------------------------------------------
inline float&
CMatrix33::operator()(unsigned int i, unsigned int j)
{
   return mV[i + 3*j];

}   // End of CMatrix33::operator()()

//-------------------------------------------------------------------------------
// @ CMatrix33::operator()()
//-------------------------------------------------------------------------------
// 2D array accessor
//-------------------------------------------------------------------------------
inline float
CMatrix33::operator()(unsigned int i, unsigned int j) const
{
   return mV[i + 3*j];

}   // End of CMatrix33::operator()()

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

#endif
