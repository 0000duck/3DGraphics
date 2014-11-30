//====================================================================================================
//	File: PointLight.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Point light object.
//====================================================================================================

#ifndef INCLUDED_POINTLIGHT_H
#define INCLUDED_POINTLIGHT_H

#include "Light.h"

class CPointLight : public CLight
{
public:
	CPointLight(const CVector3& pos);

	virtual CColor GetSurfaceColor(const SurfacePoint& sp, const CVector3& viewerPos);

	inline void SetAttenConstant(float val)		{ mAttenConstant = val; }
	inline void SetAttenLinear(float val)		{ mAttenLinear = val; }
	inline void SetAttenQuadratic(float val)	{ mAttenQuadratic = val; }

private:
	float mAttenConstant;	// Constant attenuation
	float mAttenLinear;		// Linear attenuation
	float mAttenQuadratic;	// Quadratic attenuation
};

#endif // #ifndef INCLUDED_POINTLIGHT_H