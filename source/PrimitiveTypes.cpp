#include "stdafx.h"
#include "PrimitiveTypes.h"


namespace PrimType
{

const Type CompareMode(const CString& modestr)
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

bool IsValid(int mode)
{
	return (mode > Invalid &&
			mode < NumTypes);
}

};