#include "Stdafx.h"
#include "LightManager.h"
#include "Lighting/DirectionalLight.h"
#include "Lighting/PointLight.h"
#include "Lighting/SpotLight.h"

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

CColor LightManager::GetSurfaceColor(const SurfacePoint& point)
{
	return CColor();	// stubbed
}
// --------------------------------------------------------------------

void LightManager::SetMaterialColor(LightType::Material mat, const CColor& color)
{
	switch (mat)
	{
	case LightType::WorldAmbient:
		mWorldAmbient = color;
		break;
	case LightType::Ambient:
		mAmbient = color;
		break;
	case LightType::Diffuse:
		mDiffuse = color;
		break;
	case LightType::Specular:
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