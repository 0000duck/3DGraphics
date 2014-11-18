#include "stdafx.h"
#include "CmdZBuffer.h"
#include "Utility/ScriptParser.h"
#include "Graphics/Viewport.h"

BOOL CCmdZBuffer::execute(CString &params)
{
	// Decode Parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need n params for dimensions
	const int numParams = 1;
	if (paramStrList.GetCount() != numParams)
	{
		return FALSE;
	}

	CString coord = paramStrList.GetHead();
	if (coord.Compare(L"on") == 0)
	{
		Viewport::Instance()->EnableZBuffer();
	}
	else if (coord.MakeLower().Compare(L"off") == 0)
	{
		Viewport::Instance()->DisableZBuffer();
	}
	return TRUE;
}