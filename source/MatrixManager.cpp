#include "Stdafx.h"
#include "MatrixManager.h"
#include "Vector2.h"
#include "Vector3.h"
#include "MiniMath.h"

// static singleton member initialization
MatrixManager* MatrixManager::spInstance = nullptr;

// ------------------------------------------------------------------------------------------

// Singleton accessor
MatrixManager* MatrixManager::Instance()
{
	if (!spInstance)
	{
		spInstance = new MatrixManager();
	}
	return spInstance;
}
// ------------------------------------------------------------------------------------------

// Default constructor
MatrixManager::MatrixManager()
	:	mIsLoaded(false)
{
	// Initialize to empty
	//mMatrix.Clean();
}
// ------------------------------------------------------------------------------------------

bool MatrixManager::IsLoaded()
{
	return mIsLoaded;
}
// ------------------------------------------------------------------------------------------

void MatrixManager::LoadIdentity()
{
	mMatrix.Identity();
	mIsLoaded = true;
}
// ------------------------------------------------------------------------------------------

void MatrixManager::Translate(const CVector2& v)
{
	CVector3 col0, col1, col2;
	mMatrix.GetColumns(col0, col1, col2);

	col2.x += v.x;
	col2.y += v.y;

	mMatrix.SetColumns(col0, col1, col2);
}
// ------------------------------------------------------------------------------------------

void MatrixManager::Scale(const CVector2& s)
{
	CVector3 scalevec(s.x, s.y, 1.0f);

	mMatrix.Scaling(scalevec);
}
// ------------------------------------------------------------------------------------------

void MatrixManager::Rotate(const float deg)
{
	ASSERT(deg >= 0.0f && deg <= 360.0f, "Invalid degree value");

	CMatrix33 rot;
	rot.Identity();
	rot.RotationZ(DEG2RAD(deg));
	
	mMatrix = rot * mMatrix;
}
// ------------------------------------------------------------------------------------------

void MatrixManager::Shear(const CVector2& s)
{
	CMatrix33 sm;
	sm.Identity();
	sm(0, 1) = s.x;
	sm(1, 0) = s.y;

	mMatrix *= sm;
}
// ------------------------------------------------------------------------------------------

const CMatrix33& MatrixManager::GetCurrentMatrix() const
{
	return mMatrix;
}