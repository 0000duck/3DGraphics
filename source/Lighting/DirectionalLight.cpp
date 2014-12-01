#include "stdafx.h"
#include "DirectionalLight.h"

CDirectionalLight::CDirectionalLight(const CVector3& direction)
	:	CLight(LightType::Directional)
{
	// Use position as our direction since this light has no "position"
	mPosition = direction;
}
// ------------------------------------------------------------------------------------------

float CDirectionalLight::CalculateIntensity(const CVector3& sp)
{
	// Intensity (iL) = 1, which is infinite; it can be excluded from the equation
	return 1.0f;
}
// ------------------------------------------------------------------------------------------

CColor CDirectionalLight::GetSurfaceColor(const CVertex3& sp, const CVector3& viewerPos)
{
	float intensity = CalculateIntensity(sp.Get3DPoint());

	CVector3 pointToLight = Normalize(mPosition - sp.Get3DPoint());
	CColor ambient = ComputeAmbient(intensity, sp.material.ambient);
	CColor diffuse = ComputeDiffuse(intensity, pointToLight, sp);
	CColor specular = ComputeSpecular(intensity, pointToLight,  viewerPos, sp);

	return (ambient + diffuse + specular);
}