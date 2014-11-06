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

class CVector2;

class MatrixManager : private NonCopyable
{
	// Constructor
	MatrixManager();

public:
	// Singleton accessor
	static MatrixManager* Instance();

	// Loads the identity matrix; reseting the current matrix
	void LoadIdentity();

	// Translates the current matrix
	// @param v - vector the matrix is translated by
	void Translate(const CVector2& v);

	// Scales the current matrix
	// @param s - vector the matrix is scaled by
	void Scale(const CVector2& s);

	// Rotates the current matrix
	// @param deg - amount the matrix is rotated (counter clockwise) 
	//				by in degrees around the z axis
	void Rotate(const float deg);

	// Shears the current matrix
	// @param s - vector the matrix is sheared by
	void Shear(const CVector2& s);

	// Accessors
	const CMatrix33& GetCurrentMatrix() const;

private:
	// Static instance
	static MatrixManager* spInstance;
	
	// Current primitive being drawn
	CMatrix33 mMatrix;
};

#endif // #ifndef INCLUDED_MATRIXMANAGER_H