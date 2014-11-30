#include "stdafx.h"
#include "DirectionalLight.h"

CDirectionalLight::CDirectionalLight()
	:	CLight(LightType::Directional)
{
}

CColor CDirectionalLight::GetSurfaceColor(const CVector3& surfacePoint, const CVector3& viewerPos)
{


	return CColor();
}