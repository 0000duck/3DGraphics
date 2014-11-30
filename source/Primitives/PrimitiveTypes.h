//====================================================================================================
//	File: PrimitiveTypes.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Holds a list of all the valid primitive types.
//====================================================================================================

#ifndef INCLUDED_PRIMITIVETYPES_H
#define INCLUDED_PRIMITIVETYPES_H
#pragma once

namespace PrimType
{

// Number of valid modes
const int NumTypes = 3;

enum Type
{
	Invalid = -1,
	Point,
	Line,
	Triangle
};

const CString TypeString[NumTypes] =
{
	L"point",
	L"line",
	L"triangle"
};

// Returns the mode matching the passed in string.
// If no match is found, an invalid (-1) mode is returned
inline const Type CompareMode(const CString& modestr)
{
	for (int i=0; i < NumTypes; ++i)
	{
		if (modestr.CompareNoCase(TypeString[i]) == 0)
		{
			return Type(i);
		}
	}
	return Invalid;
}

inline bool IsValid(int mode)
{
	return (mode > Invalid && mode < NumTypes);
}

} // namespace PrimType

#endif // #ifndef INCLUDED_PRIMITIVETYPES_H