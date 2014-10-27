#include "stdafx.h"
#include "CmdClip.h"
#include "ScriptParser.h"
#include "Rasterizer.h"
#include "Clipper.h"

BOOL CCmdClip::execute(CString &params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need 4 params for dimensions
	const int numParams = 1;
	if (paramStrList.GetCount() < numParams || paramStrList.GetCount() > 1)
	{
		return FALSE;
	}

	// Get the first param
	CString coord = paramStrList.GetHead();
	if (coord.Compare(L"on") == 0)
	{
		// Toggle viewport on
		Clipper::Instance()->EnableClipping();
	}
	else if (coord.MakeLower().Compare(L"off") == 0)
	{
		// Toggle viewport off
		Clipper::Instance()->DisableClipping();
	}
	return TRUE;
}
