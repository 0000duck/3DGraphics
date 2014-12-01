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
// ------------------------------------------------------------------------------------------

float CPointLight::CalculateIntensity(const CVector3& sp)
{
	float dist = Distance(mPosition, sp);

	// iL = 1 / (Kc + Kl * dist + Kq * dist^2)
	return (1.0f / (mAttenConstant + (mAttenLinear * dist) + (mAttenQuadratic * (dist * dist))));
}
// ------------------------------------------------------------------------------------------

CColor CPointLight::GetSurfaceColor(const SurfacePoint& sp, const CVector3& viewerPos)
{
	float intensity = CalculateIntensity(sp.position);

	CVector3 pointToLight = Normalize(mPosition - sp.position);
	CColor ambient = ComputeAmbient(intensity, sp.ambient);
	CColor diffuse = ComputeDiffuse(intensity, pointToLight, sp);
	CColor specular = ComputeSpecular(intensity, pointToLight,  viewerPos, sp);

	return (ambient + diffuse + specular);
}