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
// ------------------------------------------------------------------------------------------

float CSpotLight::CalculateIntensity(const CVector3& sp)
{
	float dist = Distance(mPosition, sp);

	// iL = 1 / (Kc + Kl * dist + Kq * dist^2)
	return (1.0f / (mAttenConstant + (mAttenLinear * dist) + (mAttenQuadratic * (dist * dist))));
}
// ------------------------------------------------------------------------------------------

CColor CSpotLight::GetSurfaceColor(const SurfacePoint& sp, const CVector3& viewerPos)
{
	CColor color; // init to 0; result if point not inside cone
	CVector3 pointToLight = Normalize(mPosition - sp.position); // L

	// Check if point is inside the cone
	float spot = Dot(pointToLight.Inverse(), mDirection);
	if (spot >= cosf(mAngle))
	{
		// point is inside the cone; add decay factor
		spot = powf(spot, mDecay);
		float intensity = spot / CalculateIntensity(sp.position);

		CColor ambient = ComputeAmbient(intensity, sp.ambient);
		CColor diffuse = ComputeDiffuse(intensity, pointToLight, sp);
		CColor specular = ComputeSpecular(intensity, pointToLight,  viewerPos, sp);
		color = (ambient + diffuse + specular);
	}
	return color;
}