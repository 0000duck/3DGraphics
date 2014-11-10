//====================================================================================================
//	File: Transforms.h
//	Created by: Tyler Staples
//	Date created: 06/11/2014
//	Description: 
//		Helper functions for transformation operations
//====================================================================================================

#ifndef INCLUDED_TRANSFORMS_H
#define INCLUDED_TRANSFORMS_H

class CMatrix44;
class CMatrix33;
class CVector4;
class CVector3;
class CVector2;

// Applies transformation matrix m to vector v
CVector2 Transform3HC(const CVector2& v, const CMatrix33& m);

// Returns a matrix33 that will apply transformations around the center of the object
CMatrix33 CreateTransformAroundCenter(const CVector2& pivot, const CMatrix33& m);
void TransformAroundCenter(CVector4& point, const CMatrix44& m);

#endif