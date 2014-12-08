//====================================================================================================
//	File: DirectionalLight.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Base class Light objects.
//====================================================================================================

#ifndef INCLUDED_DIRECTIONALLIGHT_H
#define INCLUDED_DIRECTIONALLIGHT_H

#include "Light.h"

class CDirectionalLight : public CLight
{
public:
	CDirectionalLight(const CVector3& direction);

	virtual void GetSurfaceColor(const CVertex3& point, const CVector3& viewerPos, CMaterial& outmat);
	virtual float CalculateIntensity(const CVector3& sp);
};

#endif	// #ifndef INCLUDED_DIRECTIONALLIGHT_H