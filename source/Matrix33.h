#pragma once

#ifndef INCLUDED_MATRIX33_H
#define INCLUDED_MATRIX33_H

#include "Vector3.h"

class CVector3;

class CMatrix33
{
public:
    // constructor/destructor
    inline CMatrix33() { Identity(); }
    inline ~CMatrix33() {}
    explicit CMatrix33(const CMatrix33& matrix);
    
    // copy operations
    CMatrix33(const CMatrix33& other);
    CMatrix33& operator=(const CMatrix33& other);

    // accessors
    float &operator()(unsigned int i, unsigned int j);
    float operator()(unsigned int i, unsigned int j) const;

    // comparison
    bool operator==(const CMatrix33& other) const;
    bool operator!=(const CMatrix33& other) const;
    bool IsZero() const;
    bool IsIdentity() const;

    // manipulators
    void SetRows(const CVector3& row1, const CVector3& row2, 
                  const CVector3& row3, const CVector3& row4); 
    void GetRows(CVector3& row1, CVector3& row2, CVector3& row3, CVector3& row4); 

    void SetColumns(const CVector3& col1, const CVector3& col2, 
                     const CVector3& col3, const CVector3& col4); 
    void GetColumns(CVector3& col1, CVector3& col2, CVector3& col3, CVector3& col4); 

    void Clean();
    void Identity();

    CMatrix33& AffineInverse();
    friend CMatrix33 AffineInverse(const CMatrix33& mat);

    CMatrix33& Transpose();
    friend CMatrix33 Transpose(const CMatrix33& mat);
        
    // transformations
    CMatrix33& Translation(const CVector3& xlate);
    CMatrix33& Rotation(const CMatrix33& matrix);
    CMatrix33& Rotation(float zRotation, float yRotation, float xRotation);
    CMatrix33& Rotation(const CVector3& axis, float angle);

    CMatrix33& Scaling(const CVector3& scale);

    CMatrix33& RotationX(float angle);
    CMatrix33& RotationY(float angle);
    CMatrix33& RotationZ(float angle);

    // member variables
	static const int kCells = 9;
    float mV[kCells];
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
   return mV[i + 4*j];

}   // End of CMatrix33::operator()()

//-------------------------------------------------------------------------------
// @ CMatrix33::operator()()
//-------------------------------------------------------------------------------
// 2D array accessor
//-------------------------------------------------------------------------------
inline float
CMatrix33::operator()(unsigned int i, unsigned int j) const
{
   return mV[i + 4*j];

}   // End of CMatrix33::operator()()

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

#endif
