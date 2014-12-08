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
#include "Containers/Vertex3.h"
#include "LightTypes.h"

class CLight
{
public:
	CLight(const LightType::Type type);

	// Computes the per-light part of the combined lighting equation
	virtual void GetSurfaceColor(const CVertex3& point, const CVector3& viewerPos, CMaterial& outmat) = 0;

	// Mutators
	void SetAmbient(const CColor& c)	{ mAmbient = c; }
	void SetDiffuse(const CColor& c)	{ mDiffuse = c; }
	void SetSpecular(const CColor& c)	{ mSpecular = c; }

	// Light type specific
	virtual float CalculateIntensity(const CVector3& pointToLight) = 0;

	virtual CColor ComputeAmbient(const float intensity, const CColor& spAmbient);
	virtual CColor ComputeDiffuse(const float intensity, const CVector3& pToL, const CVertex3& point);
	virtual CColor ComputeSpecular(const float intensity, const CVector3& pToL, const CVector3& viewerPos, const CVertex3& point);

	const CVector3& GetPosition() const { return mPosition; }

protected:
	const LightType::Type mType;
	CVector3 mPosition;
	CColor mAmbient;
	CColor mDiffuse;
	CColor mSpecular;
};

#endif	// #ifndef INCLUDED_LIGHT_H