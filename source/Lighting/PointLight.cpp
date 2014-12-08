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

void CPointLight::GetSurfaceColor(const CVertex3& sp, const CVector3& viewerPos, CMaterial& outmat)
{
	float intensity = CalculateIntensity(sp.Get3DPoint());

	CVector3 pointToLight = Normalize(mPosition - sp.Get3DPoint());
	outmat.ambient += ComputeAmbient(intensity, sp.material.ambient);
	outmat.diffuse += ComputeDiffuse(intensity, pointToLight, sp);
	outmat.specular += ComputeSpecular(intensity, pointToLight,  viewerPos, sp);
}