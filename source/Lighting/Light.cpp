#include "stdafx.h"
#include "Light.h"
#include "Graphics/PrimManager.h"

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

CColor CLight::ComputeDiffuse(const float intensity, const CVector3& pToL, const CVertex3& sp)
{
	float angle = max(0, Dot(pToL, sp.normal));
	return (intensity * angle * CColor(1,1,1) );	//mDiffuse * sp.material.diffuse);
}
// ------------------------------------------------------------------------------------------

CColor CLight::ComputeSpecular(const float intensity, const CVector3& pToL, const CVector3& viewerPos, const CVertex3& sp)
{
	CColor specular;	// initializes to 0 which is result if (L . n) < 0
	float shine = PrimManager::Instance()->GetCurrentMaterial().shine;
	if (Dot(pToL, sp.normal) > 0.0f)
	{
		CVector3 pointToViewer = Normalize(sp.Get3DPoint() - viewerPos);	
		CVector3 reflected = Reflect(pToL, sp.normal);
		float angle = pow(Dot(reflected, pointToViewer), shine);
		specular = intensity * mSpecular * max(0.0f, angle) * sp.material.specular;
	}
	return specular;
}