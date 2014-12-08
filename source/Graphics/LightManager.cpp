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

// ------------------------------------------------------------------------------------------

// Singleton accessor
LightManager* LightManager::Instance()
{
	if (!spInstance)
	{
		spInstance = new LightManager();
	}
	return spInstance;
}
// ------------------------------------------------------------------------------------------

void LightManager::DestroyInstance()
{
	if (spInstance)
	{
		spInstance->Clear();
		delete spInstance;
		spInstance = nullptr;
	}
}
// ------------------------------------------------------------------------------------------

LightManager::LightManager()
	:	mAttenConstant(0.0f)
	,	mAttenLinear(0.0f)
	,	mAttenQuadratic(0.0f)
{
}
// ------------------------------------------------------------------------------------------

LightManager::~LightManager()
{
	Clear();
}
// ------------------------------------------------------------------------------------------

void LightManager::Reset()
{
	Clear();
}
// ------------------------------------------------------------------------------------------

void LightManager::AddLight(LightPtr light)
{
	mLights.push_back(std::move(light));
}
// ------------------------------------------------------------------------------------------

void LightManager::Clear()
{
	mLights.clear();
}
// ------------------------------------------------------------------------------------------

CColor LightManager::GetSurfaceColor(const CVertex3& point)
{
	CMaterial mat;
	const CVector3& viewerpos = Camera::Instance()->GetLookFrom();
	for (auto &light : mLights)
	{
		// Each light adds their own light to the material
		light->GetSurfaceColor(point, viewerpos, mat);
	}
	// Apply the lighting to the vertex's color.
	// Specular needs to be added separately or it won't be white
	return Clamp(((mat.ambient + mat.diffuse) * point.color) + mat.specular);
}
// ------------------------------------------------------------------------------------------

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
// ------------------------------------------------------------------------------------------

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