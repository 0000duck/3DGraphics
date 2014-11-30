//====================================================================================================
//	File: FillModes.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Holds a list of all the valid fill modes along with helper functions for comparing modes.
//====================================================================================================

#ifndef INCLUDED_FILLMODES_H
#define INCLUDED_FILLMODES_H
#pragma once

namespace FillMode
{
// Number of valid modes
const int NumModes = 3;

enum Mode
{
	Invalid = -1,
	Point,			// Draws each point only
	Line,			// Draws a line between 2 points
	Fill			// TODO
};
	 
// String version of the modes
const CString ModeString[NumModes] =
{
	L"Point",
	L"Line",
	L"Fill"
};

// Returns the mode matching the passed in string.
// If no match is found, an invalid (-1) mode is returned
inline const Mode CompareMode(const CString& modestr)
{
	for (int i=0; i < NumModes; ++i)
	{
		if (modestr.CompareNoCase(ModeString[i]) == 0)
		{
			return Mode(i);
		}
	}
	return Invalid;
}

inline bool IsValid(int mode)
{
	return (mode > Invalid && mode < NumModes);
}

} // namespace FillMode

#endif // #ifndef INCLUDED_FILLMODES_H