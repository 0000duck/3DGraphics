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

class CLight
{
public:
	inline CLight(LightType::Type type)
		:	mType(type)
	{
	}

	virtual CColor GetSurfaceColor(const CVector3& surfacePoint, const CVector3& viewerPos) = 0;

protected:
	LightType::Type mType;
	CVector3 mPosition;
	CColor mAmbient;
	CColor mDiffuse;
	CColor mSpecular;
};

#endif	// #ifndef INCLUDED_LIGHT_H