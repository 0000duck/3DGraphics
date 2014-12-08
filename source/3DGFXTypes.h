//====================================================================================================
//	File: 3DGFXTypes.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: Enumeration and string list definitions for all 3DGFX types.
//====================================================================================================

#ifndef INCLUDED_3DGFXTYPES_H
#define INCLUDED_3DGFXTYPES_H
#pragma once

#define INVALID_TYPE -1

namespace PrimType
{
const int NumTypes = 3;

enum Type
{
	Invalid = -1,
	Point,
	Line,
	Triangle
};

static const CString TypeString[NumTypes] =
{
	L"point",
	L"line",
	L"triangle"
};

} // namespace PrimType

// ---------------------------------------------------------------------------

namespace FillMode
{
const int NumModes = 3;

enum Mode
{
	Invalid = -1,
	Point,			// Draws each point only
	Line,			// Draws a line between 2 points
	Fill			// Fills the primitive
};
	 
// String version of the modes
static const CString ModeString[NumModes] =
{
	L"Point",
	L"Line",
	L"Fill"
};

} // namespace FillMode

// ---------------------------------------------------------------------------

namespace ShadingMode
{
const int NumModes = 4;

enum Mode
{
	Invalid = -1,
	None,
	Flat,
	Gouraud,
	Phong
};
	 
// String version of the modes
static const CString ModeString[NumModes] =
{
	L"none",
	L"flat",
	L"gouraud",
	L"phong"
};

} // namespace ShadingMode

//====================================================================================================
// Type helpers
//====================================================================================================

// Returns the index of the typelist element that typestr matches.
// If no match is found, an -1 is returned.
inline const int GetTypeIndex(const CString& typestr, const CString* typelist, int tlistSize)
{
	for (int i=0; i < tlistSize; ++i)
	{
		if (typestr.CompareNoCase(typelist[i]) == 0)
		{
			return i;
		}
	}
	return INVALID_TYPE;
}

// Range check
inline bool IsValidType(int index, int numTypes)
{
	return (index > INVALID_TYPE && index < numTypes);
}

#endif // #ifndef INCLUDED_PRIMITIVETYPES_H