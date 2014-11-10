#include "stdafx.h"
#include "CmdFillMode.h"
#include "Utility/ScriptParser.h"
#include "Graphics/Rasterizer.h"
#include "Graphics/StateManager.h"


BOOL CCmdFillMode::execute(CString &params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need at least 1 param for mode
	const int numParams = 1;
	if (paramStrList.GetCount() < numParams)
	{
		return FALSE;
	}

	CString modestr = paramStrList.GetHead();
	int mode = FillMode::CompareMode(modestr);
	
	// Set the fill mode
	StateManager::Instance()->SetFillMode(FillMode::Mode(mode));

	return TRUE;
}
