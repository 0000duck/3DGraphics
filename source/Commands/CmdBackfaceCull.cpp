#include "stdafx.h"
#include "CmdBackfaceCull.h"
#include "Utility/ScriptParser.h"
#include "Graphics/Viewport.h"

BOOL CCmdBackfaceCull::execute(CString &params)
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

	// Get the first param
	CString coord = paramStrList.GetHead();
	if (coord.Compare(L"on") == 0)
	{
		Viewport::Instance()->EnableBackfaceCulling();
	}
	else if (coord.MakeLower().Compare(L"off") == 0)
	{
		Viewport::Instance()->DisableBackfaceCulling();
	}
	return TRUE;
}