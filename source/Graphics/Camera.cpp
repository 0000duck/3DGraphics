#include "Stdafx.h"
#include "Camera.h"
#include "PerspectiveMatrix.h"
#include "Viewport.h"

// static singleton member initialization
Camera* Camera::spInstance = nullptr;

// ------------------------------------------------------------------------------------------

// Singleton accessor
Camera* Camera::Instance()
{
	if (!spInstance)
	{
		spInstance = new Camera();
	}
	return spInstance;
}
// ------------------------------------------------------------------------------------------

void Camera::DestroyInstance()
{
	if (spInstance)
	{
		delete spInstance;
		spInstance = nullptr;
	}
}
// ------------------------------------------------------------------------------------------

// Default constructor
Camera::Camera()
	:	mInitialized(false)
	,	mFOV(90.0f)
	,	mProjectionPlane(0.0f)
	,	mNear(0.1f)
	,	mFar(1000.0f)
{
}
// ------------------------------------------------------------------------------------------

void Camera::Reset()
{
	mInitialized = false;
	mFOV = 90.0f;
	mProjectionPlane = 0.0f;
	mNear = 0.1f;
	mFar = 1000.0f;

	mLookFrom.Zero();
	mLookAt.Zero();
	mLookUp.Zero();
	mLookSide.Zero();

	mViewToWorld.Identity();
	mWorldToView.Identity();
	mPerspective.Identity();
}
// ------------------------------------------------------------------------------------------

void Camera::Create(const CVector3& origin, const CVector3& interest)
{
	mLookFrom = origin;
	mLookAt = interest;

	// The lookside vector should lay flat in the xz-plane; perpendicular the the y axis
	CVector3 vz = Normalize(mLookAt - mLookFrom);
	mLookSide = Cross(CVector3::yAxis, vz);

	// The up vector is perpendicular to the lookat, and look side
	mLookUp = Cross(vz, mLookSide);

	// Calculate the rest of the orthonormal view frame axes
	CVector3 vx = Normalize(Cross(vz, mLookUp));
	CVector3 vy = Cross(vx, vz);

	// Create the view to world matrix
	CVector4 c0, c1, c2, c3;
	mViewToWorld.GetColumns(c0, c1, c2, c3);
	c0.Set(vx.x, vx.y, vx.z, 0.0f);
	c1.Set(vy.x, vy.y, vy.z, 0.0f);
	c2.Set(vz.x, vz.y, vz.z, 0.0f);
	c3.Set(mLookFrom.x, mLookFrom.y, mLookFrom.z, 1.0f);
	mViewToWorld.SetColumns(c0, c1, c2, c3);

	// Create the World to view matrix.
	// AffineInverse is needed since the matrix is not ortho-normal
	mWorldToView = AffineInverse(mViewToWorld);

	// Get the perspective projection matrix
	float aspectratio = Viewport::Instance()->GetAspectRatio();
	mPerspective = ComputeProjectionMatrix(mFOV, aspectratio, mNear, mFar);

	// Camera is now set
	mInitialized = true;
}