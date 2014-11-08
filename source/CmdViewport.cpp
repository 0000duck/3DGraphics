#include "stdafx.h"
#include "CmdViewport.h"
#include "ScriptParser.h"
#include "Viewport.h"

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

	float coords[numParams];
	POSITION coord = paramStrList.GetHeadPosition();
	for (int i = 0; i < numParams; i++)
	{
		CString paramStr = paramStrList.GetNext(coord);
		coords[i] = (float)(wcstod(paramStr, NULL));
	}

	// Set the viewport with the input dimensions
	Viewport::Instance()->Set(coords[0], coords[1], coords[2], coords[3]);

	return TRUE;
}
