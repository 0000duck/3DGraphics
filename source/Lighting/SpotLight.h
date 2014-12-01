//====================================================================================================
//	File: Light.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Base class Light objects.
//====================================================================================================

#ifndef INCLUDED_SPOTLIGHT_H
#define INCLUDED_SPOTLIGHT_H

#include "Light.h"

class CSpotLight : public CLight
{
public:
	CSpotLight(const CVector3& pos, const CVector3& direction, float angle, float decay);

	virtual CColor GetSurfaceColor(const SurfacePoint& sp, const CVector3& viewerPos);
	virtual float CalculateIntensity(const CVector3& sp);

	inline void SetAttenConstant(float val)		{ mAttenConstant = val; }
	inline void SetAttenLinear(float val)		{ mAttenLinear = val; }
	inline void SetAttenQuadratic(float val)	{ mAttenQuadratic = val; }

private:
	float mAttenConstant;	// Constant attenuation
	float mAttenLinear;		// Linear attenuation
	float mAttenQuadratic;	// Quadratic attenuation

	float mAngle;			// Angle of the spotlight cone (rads)
	float mDecay;			// Decay factor of brightness in center of cone to edge
	CVector3 mDirection;	// Direction the light is facing
};

#endif	// #ifndef INCLUDED_SPOTLIGHT_H