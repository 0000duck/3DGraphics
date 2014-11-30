//====================================================================================================
//	File: LightManager.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Keeps track of the all light related attributes.
//		To use this class, use the static accessor by calling LightManager::Instance().
//====================================================================================================

#ifndef INCLUDED_LIGHTMANAGER_H
#define INCLUDED_LIGHTMANAGER_H
#pragma once

#include "Utility/NonCopyable.h"
#include "Containers/Color.h"
#include "Lighting/Light.h"
#include <vector>

// This struct may get replaced when the details of the next assignment are given.
struct SurfacePoint
{
	CVector3 position;
	CVector3 normal;
	CColor material;
};

class LightManager : private NonCopyable
{
	// Constructors
	LightManager();
	~LightManager();

	typedef std::vector<CLight*> Lights;
public:

	// Singleton accessor
	static LightManager* Instance();
	static void DestroyInstance();

	// Resets all data members to default values
	void Reset();

	// Allocates a new light of the param type and adds it to the global list.
	// New lights are created with the current ambient/diffuse/specular values.
	// Point and spot lights are also given the current attenuation values.
	void CreateLight(LightType::Type type);

	// Obtains ownership of an existing light and adds it to the global list.
	void AddLight(CLight* light);

	// Deletes the global list of lights
	void Clear();

	CColor GetSurfaceColor(const SurfacePoint& point);

private:
	static LightManager* spInstance;

	CColor mWorldAmbient;
	CColor mAmbient;			// Current ambient
	CColor mDiffuse;			// Current diffuse
	CColor mSpecular;			// Current specular

	float mAttenConstant;		// Current constant attenuation
	float mAttenLinear;			// Current linear attenuation
	float mAttenQuadratice;		// Current quadratic attenuation

	Lights mLights;				// Global list of lights in the scene
};

#endif	// #ifndef INCLUDED_LIGHTMANAGER_H