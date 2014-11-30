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
	CSpotLight();

	virtual CColor GetSurfaceColor(const CVector3& surfacePoint, const CVector3& viewerPos);

private:
	float mAttenConstant;	// Constant attenuation
	float mAttenLinear;		// Linear attenuation
	float mAttenQuadratice;	// Quadratic attenuation

	float mAngle;			// Angle of the spotlight cone
	float mDecay;			// Decay factor of brightness in center of cone to edge
	CVector3 mDirection;	// Direction the light is facing
};

#endif	// #ifndef INCLUDED_SPOTLIGHT_H