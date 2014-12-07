#include "stdafx.h"
#include "CmdShadingMode.h"
#include "Utility/ScriptParser.h"
#include "Graphics/StateManager.h"

BOOL CCmdShadingMode::execute(CString &params)
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
	int mode = GetTypeIndex(coord, ShadingMode::ModeString, ShadingMode::NumModes);
	StateManager::Instance()->SetShadingMode(ShadingMode::Mode(mode));

	return TRUE;
}