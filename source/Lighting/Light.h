//====================================================================================================
//	File: Light.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Base class Light objects.
//====================================================================================================

#ifndef INCLUDED_LIGHT_H
#define INCLUDED_LIGHT_H

#include "Containers/Vector3.h"
#include "Containers/Color.h"
#include "LightTypes.h"

// This struct may get replaced when the details of the next assignment are given.
struct SurfacePoint
{
	CVector3 position;
	CVector3 normal;
	CColor ambient;
	CColor diffuse;
	CColor specular;
	CColor emissive;
};

class CLight
{
public:
	CLight(const LightType::Type type);

	// Computes the per-light part of the combined lighting equation
	virtual CColor GetSurfaceColor(const SurfacePoint& sp, const CVector3& viewerPos) = 0;

	// Mutators
	void SetAmbient(const CColor& c)	{ mAmbient = c; }
	void SetDiffuse(const CColor& c)	{ mDiffuse = c; }
	void SetSpecular(const CColor& c)	{ mSpecular = c; }

protected:
	// Light type specific
	virtual float CalculateIntensity(const CVector3& pointToLight) = 0;

	virtual CColor ComputeAmbient(const float intensity, const CColor& spAmbient);
	virtual CColor ComputeDiffuse(const float intensity, const CVector3& pToL, const SurfacePoint& sp);
	virtual CColor ComputeSpecular(const float intensity, const CVector3& pToL, const CVector3& viewerPos, const SurfacePoint& sp);

protected:
	const LightType::Type mType;
	CVector3 mPosition;
	CColor mAmbient;
	CColor mDiffuse;
	CColor mSpecular;
};

#endif	// #ifndef INCLUDED_LIGHT_H