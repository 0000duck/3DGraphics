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
	,	mAttenQuadratice(0.0f)
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

void LightManager::CreateLight(LightType::Type type)
{
	switch (type)
	{
	case LightType::Directional:
		mLights.push_back(new CDirectionalLight());
		break;
	case LightType::Point:
		mLights.push_back(new CPointLight());
		break;
	case LightType::Spotlight:
		mLights.push_back(new CSpotLight());
		break;
	}
}
// --------------------------------------------------------------------

void LightManager::AddLight(CLight* light)
{
	mLights.push_back(light);
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