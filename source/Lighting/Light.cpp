#include "stdafx.h"
#include "Light.h"

CLight::CLight(const LightType::Type type)
	:	mType(type)
{
}
// ------------------------------------------------------------------------------------------

CColor CLight::ComputeAmbient(const float intensity, const CColor& spAmbient)
{
	return (intensity * (mAmbient * spAmbient));
}
// ------------------------------------------------------------------------------------------

CColor CLight::ComputeDiffuse(const float intensity, const CVector3& pToL, const SurfacePoint& sp)
{
	float angle = max(0, Dot(pToL, sp.normal));
	return (intensity * angle * mDiffuse * sp.diffuse);
}
// ------------------------------------------------------------------------------------------

CColor CLight::ComputeSpecular(const float intensity, const CVector3& pToL, const CVector3& viewerPos, const SurfacePoint& sp)
{
	int shine = 16;		// temp hard coded exponent
	CColor specular;	// initializes to 0 which is result if (L . n) < 0
	if (Dot(pToL, sp.normal) > 0.0f)
	{
		CVector3 pointToViewer = sp.position - viewerPos;	
		CVector3 reflected = Reflect(pToL, sp.normal);
		float angle = pow(Dot(reflected, pointToViewer), shine);
		specular = intensity * mSpecular * max(0.0f, angle) * sp.specular;
	}
	return specular;
}