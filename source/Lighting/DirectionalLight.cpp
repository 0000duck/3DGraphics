#include "stdafx.h"
#include "DirectionalLight.h"
#include "Containers/Color.h"


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

void CDirectionalLight::GetSurfaceColor(const CVertex3& sp, const CVector3& viewerPos, CMaterial& outmat)
{
	float intensity = 1.0f;

	CVector3 pointToLight = Normalize(-mPosition);
	outmat.ambient += ComputeAmbient(intensity, sp.material.ambient);
	outmat.diffuse += ComputeDiffuse(intensity, pointToLight, sp);
	outmat.specular += ComputeSpecular(intensity, pointToLight, viewerPos, sp);
}