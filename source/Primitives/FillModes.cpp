#include "stdafx.h"
#include "FillModes.h"


namespace FillMode
{

const Mode CompareMode(const CString& modestr)
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

bool IsValid(int mode)
{
	return (mode > Invalid &&
			mode < NumModes);
}

};