#include "StdAfx.h"
#include "CmdColor.h"
#include "ScriptParser.h"
#include "Rasterizer.h"
#include "StateManager.h"


BOOL CCmdColor::execute(CString &params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need at least 3 params for r, g, b
	const int numParams = 3;
	if (paramStrList.GetCount() < numParams)
	{
		return FALSE;
	}

	float rgb[numParams];
	POSITION color = paramStrList.GetHeadPosition();
	for (int i = 0; i < numParams; i++)
	{
		CString paramStr = paramStrList.GetNext(color);
		rgb[i] = (float)(wcstod(paramStr, NULL));
	}

	// Set the color in the state manager
	StateManager::Instance()->SetColor(rgb[0], rgb[1], rgb[2]);

	CRasterizer::Instance()->SetColor(rgb[0], rgb[1], rgb[2]);

	return TRUE;
}
