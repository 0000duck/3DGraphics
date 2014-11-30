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

	virtual CColor GetSurfaceColor(const CVector3& surfacePoint, const CVector3& viewerPos);
};

#endif	// #ifndef INCLUDED_DIRECTIONALLIGHT_H