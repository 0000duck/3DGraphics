#include "StdAfx.h"
#include "CmdColor.h"
#include "Utility/ScriptParser.h"
#include "Graphics/Rasterizer.h"
#include "Graphics/StateManager.h"


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

	// Convert the params to a float array
	float rgb[numParams];
	CScriptParser::ToArray(paramStrList, numParams, rgb);

	// Set the color in the state manager
	StateManager::Instance()->SetColor(rgb[0], rgb[1], rgb[2]);
	CRasterizer::Instance()->SetColor(rgb[0], rgb[1], rgb[2]);

	return TRUE;
}
