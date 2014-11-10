#include "stdafx.h"
#include "CmdViewport.h"
#include "Utility/ScriptParser.h"
#include "Graphics/Viewport.h"

BOOL CCmdViewport::execute(CString &params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need 4 params for dimensions
	const int numParams = 4;
	if (paramStrList.GetCount() < numParams)
	{
		return FALSE;
	}

	float args[numParams];
	CScriptParser::ToArray(paramStrList, numParams, args);

	// Set the viewport with the input dimensions
	Viewport::Instance()->Set(args[0], args[1], args[2], args[3]);

	return TRUE;
}
