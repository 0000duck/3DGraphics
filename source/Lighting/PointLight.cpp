#include "stdafx.h"
#include "PointLight.h"

CPointLight::CPointLight(const CVector3& pos)
	:	CLight(LightType::Point)
	,	mAttenConstant(0.0f)
	,	mAttenLinear(0.0f)
	,	mAttenQuadratic(0.0f)
{
	mPosition = pos;
}

CColor CPointLight::GetSurfaceColor(const SurfacePoint& sp, const CVector3& viewerPos)
{
	return CColor();
}