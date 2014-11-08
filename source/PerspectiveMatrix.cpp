#include "stdafx.h"
#include "Matrix44.h"
#include "MiniMath.h"

// Compute projection matrix
// FOVDegrees are passed in as degrees then converted to radians
CMatrix44 ComputeProjectionMatrix( float FOVDegrees, float fAspectRatio, float fNear, float fFar)
{
	float projectionPlane = 1.0f / tanf( DEG2RAD(FOVDegrees) / 2.0f );
	float Near = projectionPlane + fNear;
	float Far = projectionPlane + fFar;
	float denom = Far - Near;

	CMatrix44 ProjectionMatrix;
	ProjectionMatrix.Identity();
	ProjectionMatrix[0] = projectionPlane / fAspectRatio;
	ProjectionMatrix[5] = projectionPlane;
    ProjectionMatrix[10] = ( Far + Near ) / denom;
	ProjectionMatrix[11] = 1.0f;
	ProjectionMatrix[14] = (-2.0f * Near * Far ) / denom;
	ProjectionMatrix[15] = 0.0f;

	return ProjectionMatrix;
}