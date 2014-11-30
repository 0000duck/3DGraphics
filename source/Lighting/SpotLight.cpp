#include "stdafx.h"
#include "SpotLight.h"

CSpotLight::CSpotLight()
	:	CLight(LightType::Spotlight)
	,	mAttenConstant(0.0f)
	,	mAttenLinear(0.0f)
	,	mAttenQuadratice(0.0f)
{
}

CColor CSpotLight::GetSurfaceColor(const CVector3& surfacePoint, const CVector3& viewerPos)
{
	return CColor();
}