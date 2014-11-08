//====================================================================================================
//	File: MatrixManager.h
//	Created by: Tyler Staples
//	Date created: 05/11/2014
//	Description: 
//		Keeps track of the current transformation matrix.
//		To use this class, use the static accessor by calling MatrixManager::Instance().
//====================================================================================================

#ifndef INCLUDED_MATRIXMANAGER_H
#define INCLUDED_MATRIXMANAGER_H
#pragma once

#include "NonCopyable.h"
#include "Matrix33.h"
#include "Matrix44.h"

class CVector2;
class CVector3;

class MatrixManager : private NonCopyable
{
	// Constructor
	MatrixManager();

public:
	// Singleton accessor
	static MatrixManager* Instance();

	// Returns if true if the matrix has been initialized
	bool IsLoaded2D();
	bool IsLoaded3D();

	// Loads the identity matrix; reseting the current matrix
	void LoadIdentity2D();
	void LoadIdentity3D();

	// Translates the current matrix
	// @param v - vector the matrix is translated by
	void Translate2D(const CVector2& v);
	void Translate3D(const CVector3& v);

	// Scales the current matrix
	// @param s - vector the matrix is scaled by
	void Scale2D(const CVector2& s);
	void Scale3D(const CVector3& s);

	// Rotates the current matrix
	// @param deg - amount the matrix is rotated (counter clockwise) 
	//				by in degrees around the z axis
	void Rotate2D(const float deg);
	void Rotate3D(const float deg);

	// Shears the current matrix
	// @param s - vector the matrix is sheared by
	void Shear2D(const CVector2& s);

	// Accessors
	const CMatrix33& GetMatrix2D() const;
	const CMatrix44& GetMatrix3D() const;

private:
	// Static instance
	static MatrixManager* spInstance;
	
	// Current primitive being drawn
	CMatrix33 mMatrix33;
	CMatrix44 mMatrix44;
};

#endif // #ifndef INCLUDED_MATRIXMANAGER_H