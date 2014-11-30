#include "stdafx.h"
#include "DirectionalLight.h"

CDirectionalLight::CDirectionalLight(const CVector3& direction)
	:	CLight(LightType::Directional)
{
	// Use position as our direction since this light has no "position"
	mPosition = direction;
}

CColor CDirectionalLight::GetSurfaceColor(const CVector3& surfacePoint, const CVector3& viewerPos)
{
	return CColor();
}