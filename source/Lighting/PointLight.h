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
	CPointLight();

	virtual CColor GetSurfaceColor(const CVector3& surfacePoint, const CVector3& viewerPos);

private:
	float mAttenConstant;	// Constant attenuation
	float mAttenLinear;		// Linear attenuation
	float mAttenQuadratice;	// Quadratic attenuation
};

#endif // #ifndef INCLUDED_POINTLIGHT_H