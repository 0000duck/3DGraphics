#include "stdafx.h"
#include "PointLight.h"

CPointLight::CPointLight()
	:	CLight(LightType::Point)
	,	mAttenConstant(0.0f)
	,	mAttenLinear(0.0f)
	,	mAttenQuadratice(0.0f)
{
}

CColor CPointLight::GetSurfaceColor(const CVector3& surfacePoint, const CVector3& viewerPos)
{
	return CColor();
}