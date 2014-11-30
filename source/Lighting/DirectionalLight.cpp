#include "stdafx.h"
#include "DirectionalLight.h"

CDirectionalLight::CDirectionalLight(const CVector3& direction)
	:	CLight(LightType::Directional)
{
	// Use position as our direction since this light has no "position"
	mPosition = direction;
}

CColor CDirectionalLight::GetSurfaceColor(const SurfacePoint& sp, const CVector3& viewerPos)
{
	// Intensity (iL) = 1, which is infinite; it can be excluded from the equation

	// ambient
	CColor ambient(mAmbient * sp.ambient);
	
	// diffuse
	CVector3 pointToLight = mPosition - sp.position; // L
	CColor diffuse = (max(0, Dot(pointToLight, sp.normal))) * mDiffuse * sp.diffuse;

	// specular
	int shine = 16; // temp hard coded exponent
	CColor specular; // initializes to 0 which is result if (L . n) < 0
	if (Dot(pointToLight, sp.normal) > 0.0f)
	{
		CVector3 pointToViewer = sp.position - viewerPos;			// v
		CVector3 reflected = Reflect(pointToLight, sp.normal);		// r
		float angle = pow(Dot(reflected, pointToViewer), shine);	// max(0, r . v)^shine
		specular = mSpecular * max(0.0f, angle) * sp.specular;
	}
	return (ambient + diffuse + specular);
}