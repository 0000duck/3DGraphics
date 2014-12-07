#include "Stdafx.h"
#include "LightManager.h"
#include "Lighting/DirectionalLight.h"
#include "Lighting/PointLight.h"
#include "Lighting/SpotLight.h"
#include "Primitives/Primitive.h"
#include "Camera.h"
#include "StateManager.h"

// static singleton member initialization
LightManager* LightManager::spInstance = nullptr;

// --------------------------------------------------------------------

// Singleton accessor
LightManager* LightManager::Instance()
{
	if (!spInstance)
	{
		spInstance = new LightManager();
	}
	return spInstance;
}
// --------------------------------------------------------------------

void LightManager::DestroyInstance()
{
	if (spInstance)
	{
		delete spInstance;
		spInstance = nullptr;
	}
}
// --------------------------------------------------------------------

LightManager::LightManager()
	:	mAttenConstant(0.0f)
	,	mAttenLinear(0.0f)
	,	mAttenQuadratic(0.0f)
{
}
// --------------------------------------------------------------------

LightManager::~LightManager()
{
	Clear();
}
// --------------------------------------------------------------------

void LightManager::Reset()
{
	Clear();
}
// --------------------------------------------------------------------

void LightManager::AddLight(CLight* light)
{
	mLights.push_back(std::move(light));
}
// --------------------------------------------------------------------

void LightManager::Clear()
{
	const int sz = mLights.size();
	for (int i=0; i < sz; ++i)
	{
		delete mLights[i];
	}
	mLights.clear();
}
// --------------------------------------------------------------------

CColor LightManager::GetSurfaceColor(const CVertex3& point)
{
	const CVector3& viewerpos = Camera::Instance()->GetLookFrom();
	CColor color;
	for (auto light : mLights)
	{
		// Get the sum of the intermediate per-light values from all the lights
		color += light->GetSurfaceColor(point, viewerpos);
	}
	// Me + Wa * Ma + SumLights(Ca + Cd + Cs)
	//return ((mWorldAmbient * point.material.ambient) + point.material.emissive) + color;
	return (point.material.ambient + point.material.emissive) + color;
}
// --------------------------------------------------------------------

CColor LightManager::ComputeLighting(CVertex3& point)
{
	ShadingMode::Mode shadingmode = StateManager::Instance()->GetShadingMode();
	switch (shadingmode)
	{
	case ShadingMode::Flat:
		return ComputeFlatShading(point);
	case ShadingMode::Gouraud:
		return ComputeGouraudShading(point);
	}
	return CColor(1.0f, 1.0f, 1.0f);
}

CColor LightManager::ComputeFlatShading(CVertex3& point)
{
	//CVector2 midpoint = prim->GetPivot();
	//float z = prim->GetZDepth();
	//CVector3 v3(midpoint.x, midpoint.y, z);

	return GetSurfaceColor(point);
}

CColor LightManager::ComputeGouraudShading(CVertex3& point)
{
	return GetSurfaceColor(point);
}

void LightManager::SetMaterialColor(Material::Type mat, const CColor& color)
{
	switch (mat)
	{
	case Material::WorldAmbient:
		mWorldAmbient = color;
		break;
	case Material::Ambient:
		mAmbient = color;
		break;
	case Material::Diffuse:
		mDiffuse = color;
		break;
	case Material::Specular:
		mSpecular = color;
		break;
	}
}
// --------------------------------------------------------------------

void LightManager::SetAttenuation(LightType::Attenuation atten, float val)
{
	switch (atten)
	{
	case LightType::Constant:
		mAttenConstant = val;
		break;
	case LightType::Linear:
		mAttenLinear = val;
		break;
	case LightType::Quadratic:
		mAttenQuadratic = val;
		break;
	}
}