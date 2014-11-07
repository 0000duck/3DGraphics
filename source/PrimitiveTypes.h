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
	const Type CompareMode(const CString& typestr);

	bool IsValid(int mode);
};

#endif