#include "stdafx.h"
#include "CmdClearLights.h"
#include "Utility/ScriptParser.h"
#include "Graphics/LightManager.h"

BOOL CCmdClearLights::execute(CString &params)
{
	// Decode Parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need n params for dimensions
	const int numParams = 0;
	if (paramStrList.GetCount() != numParams)
	{
		return FALSE;
	}

	LightManager::Instance()->Clear();

	return TRUE;
}