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
	inline CLight(LightType::Type type)
		:	mType(type)
	{
	}

	virtual CColor GetSurfaceColor(const SurfacePoint& sp, const CVector3& viewerPos) = 0;

	void SetAmbient(const CColor& c)	{ mAmbient = c; }
	void SetDiffuse(const CColor& c)	{ mDiffuse = c; }
	void SetSpecular(const CColor& c)	{ mSpecular = c; }

protected:
	LightType::Type mType;
	CVector3 mPosition;
	CColor mAmbient;
	CColor mDiffuse;
	CColor mSpecular;
};

#endif	// #ifndef INCLUDED_LIGHT_H