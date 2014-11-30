#include "stdafx.h"
#include "SpotLight.h"

CSpotLight::CSpotLight(const CVector3& pos, const CVector3& direction, float angle, float decay)
	:	CLight(LightType::Spotlight)
	,	mAttenConstant(0.0f)
	,	mAttenLinear(0.0f)
	,	mAttenQuadratic(0.0f)
	,	mDirection(direction)
	,	mAngle(angle)
	,	mDecay(decay)
{
	mPosition = pos;
}

CColor CSpotLight::GetSurfaceColor(const SurfacePoint& spt, const CVector3& viewerPos)
{
	return CColor();
}