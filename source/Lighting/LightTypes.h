//====================================================================================================
//	File: LightTypes.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Type info for lighting.
//====================================================================================================

#ifndef INCLUDED_LIGHTTYPES_H
#define INCLUDED_LIGHTTYPES_H
#pragma once

namespace LightType
{

// Number of valid modes
const int NumTypes = 3;

enum Type
{
	Directional,
	Point,
	Spotlight
};

enum Material
{
	WorldAmbient,
	Ambient,
	Diffuse,
	Specular
};

enum Attenuation
{
	Constant,
	Linear,
	Quadratic
};

} // namespace LightType

#endif // #ifndef INCLUDED_LIGHTTYPES_H