#include "Stdafx.h"
#include "MatrixManager.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
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
{
}
// ------------------------------------------------------------------------------------------

bool MatrixManager::IsLoaded2D()
{
	return (!mMatrix33.IsIdentity() && !mMatrix33.IsZero());
}
// ------------------------------------------------------------------------------------------

bool MatrixManager::IsLoaded3D()
{
	return (!mMatrix44.IsIdentity() && !mMatrix44.IsZero());
}
// ------------------------------------------------------------------------------------------

void MatrixManager::LoadIdentity2D()
{
	mMatrix33.Identity();
}
// ------------------------------------------------------------------------------------------

void MatrixManager::LoadIdentity3D()
{
	mMatrix44.Identity();
}
// ------------------------------------------------------------------------------------------

void MatrixManager::Translate2D(const CVector2& v)
{
	CVector3 col0, col1, col2;
	mMatrix33.GetColumns(col0, col1, col2);

	col2.x += v.x;
	col2.y += v.y;

	mMatrix33.SetColumns(col0, col1, col2);
}
// ------------------------------------------------------------------------------------------

void MatrixManager::Translate3D(const CVector3& v)
{
	CVector4 col0, col1, col2, col3;
	mMatrix44.GetColumns(col0, col1, col2, col3);

	col3.x += v.x;
	col3.y += v.y;
	col3.z += v.z;

	mMatrix44.SetColumns(col0, col1, col2, col3);
}
// ------------------------------------------------------------------------------------------

void MatrixManager::Scale2D(const CVector2& s)
{
	CVector3 scalevec(s.x, s.y, 1.0f);
	mMatrix33.Scaling(scalevec);
}
// ------------------------------------------------------------------------------------------

void MatrixManager::Scale3D(const CVector3& s)
{
	CVector3 scalevec(s.x, s.y, s.z);
	mMatrix44.Scaling(scalevec);
}
// ------------------------------------------------------------------------------------------

void MatrixManager::Rotate2D(const float deg)
{
	ASSERT(deg >= 0.0f && deg <= 360.0f, "Invalid degree value");

	CMatrix33 rot;
	rot.Identity();
	rot.RotationZ(DEG2RAD(deg));
	
	mMatrix33 = rot * mMatrix33;
}
// ------------------------------------------------------------------------------------------

void MatrixManager::Rotate3D(const float deg)
{
	ASSERT(deg >= 0.0f && deg <= 360.0f, "Invalid degree value");

	CMatrix44 rot;
	rot.Identity();
	rot.RotationZ(DEG2RAD(deg));
	
	mMatrix44 = rot * mMatrix44;
}
// ------------------------------------------------------------------------------------------

void MatrixManager::Shear2D(const CVector2& s)
{
	CMatrix33 sm;
	sm.Identity();
	sm(0, 1) = s.x;
	sm(1, 0) = s.y;

	mMatrix33 *= sm;
}
// ------------------------------------------------------------------------------------------

const CMatrix33& MatrixManager::GetMatrix2D() const
{
	return mMatrix33;
}
// ------------------------------------------------------------------------------------------

const CMatrix44& MatrixManager::GetMatrix3D() const
{
	return mMatrix44;
}