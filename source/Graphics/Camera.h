//====================================================================================================
//	File: Camera.h
//	Created by: Tyler Staples
//	Date created: 07/11/2014
//	Description: 
//		Keeps track of the current camera.
//		Uses a left-handed coordinate system; z-axis is pointing into the scene from the camera.
//		To use this class, use the static accessor by calling Camera::Instance().
//====================================================================================================

#ifndef INCLUDED_CAMERA_H
#define INCLUDED_CAMERA_H
#pragma once

#include "Utility/NonCopyable.h"
#include "Containers/Vector3.h"
#include "Containers/Matrix44.h"

class Camera : private NonCopyable
{
	// Constructor
	Camera();

public:
	// Singleton accessor
	static Camera* Instance();
	// Destroys the current instance of this class.
	static void DestroyInstance();

	// Resets all data members to default values
	void Reset();

	// Creates a camera.
	// @param origin - where the camera is located in 3D space
	// @param interest - what the camera is looking at
	void Create(const CVector3& origin, const CVector3& interest);

	// Setters
	inline void SetFOV(float deg)	{ mFOV = deg; }
	inline void SetNear(float n)	{ mNear = n; }
	inline void SetFar(float f)		{ mFar = f; }

	// Accessors
	inline float GetNear() const	{ return mNear; }
	inline float GetFar() const		{ return mFar; }
	inline float GetFOV() const		{ return mFOV; }

	inline const CMatrix44& GetViewToWorldMatrix() const { return mViewToWorld; }
	inline const CMatrix44& GetWorldToViewMatrix() const { return mWorldToView; }
	inline const CMatrix44& GetPerspectiveMatrix() const { return mPerspective; }

	inline CVector3 GetLookDirection() const	{ return mLookAt - mLookFrom; }
	inline const CVector3& GetLookFrom() const	{ return mLookFrom; }
	inline const CVector3& GetLookAt() const	{ return mLookAt; }

private:
	// Static instance
	static Camera* spInstance;

	bool mInitialized;		// Has the camera been created

	CVector3 mLookFrom;		// Camera origin
	CVector3 mLookAt;		// Camera interest
	CVector3 mLookUp;		// Camera up-vector	(unit vector)
	CVector3 mLookSide;		// Orthonormal basis vector

	float mFOV;				// Camera field-of-view (assumes 90deg)
	float mProjectionPlane; // Z dist to projection plane
	float mNear;			// Z dist to near plane
	float mFar;				// Z dist to far plane

	CMatrix44 mViewToWorld;	// Transforms a point from view frame to world frame
	CMatrix44 mWorldToView;	// Transforms a point from world frame to view frame
	CMatrix44 mPerspective;	// Perspective Projection matrix
};

#endif // #ifndef INCLUDED_CAMERA_H