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
#include "Containers/Material.h"
#include "Lighting/Light.h"
#include <vector>

class CPrimitive;

class LightManager : private NonCopyable
{
	// Constructors
	LightManager();
	~LightManager();

	typedef std::unique_ptr<CLight> LightPtr;
	typedef std::vector<LightPtr> Lights;
public:

	// Singleton accessor
	static LightManager* Instance();
	static void DestroyInstance();

	// Resets all data members to default values
	void Reset();

	// Obtains ownership of an existing light and adds it to the global list.
	// New lights are created with the current ambient/diffuse/specular values.
	// Point and spot lights are also given the current attenuation values.
	void AddLight(LightPtr light);

	// Deletes the global list of lights
	void Clear();

	// Computes the color at the given surface point with the combined lighting equation
	CColor GetSurfaceColor(const CVertex3& point);

	CColor ComputeLighting(CVertex3& point);
	CColor ComputeFlatShading(CVertex3& point);
	CColor ComputeGouraudShading(CVertex3& point);

	inline bool SceneHasLights() const { return (mLights.size() > 0); }

public:	// Mutators/Accessors
	void SetMaterialColor(Material::Type mat, const CColor& color);
	void SetAttenuation(LightType::Attenuation atten, float val);

	inline const CColor& GetWorldAmbient() const	{ return mWorldAmbient; }
	inline const CColor& GetAmbient() const			{ return mAmbient; }
	inline const CColor& GetDiffuse() const			{ return mDiffuse; }
	inline const CColor& GetSpecular() const		{ return mSpecular; }

	inline float GetAttenConstant() const			{ return mAttenConstant; }
	inline float GetAttenLinear() const				{ return mAttenLinear; }
	inline float GetAttenQuadratic() const			{ return mAttenQuadratic; }

private:
	static LightManager* spInstance;

	CColor mWorldAmbient;
	CColor mAmbient;			// Current ambient
	CColor mDiffuse;			// Current diffuse
	CColor mSpecular;			// Current specular

	float mAttenConstant;		// Current constant attenuation
	float mAttenLinear;			// Current linear attenuation
	float mAttenQuadratic;		// Current quadratic attenuation

	Lights mLights;				// Global list of lights in the scene
};

#endif	// #ifndef INCLUDED_LIGHTMANAGER_H