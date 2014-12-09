#include "stdafx.h"
#include "CmdClearTextures.h"
#include "Utility/ScriptParser.h"
#include "Graphics/TextureManager.h"

BOOL CCmdClearTextures::execute(CString &params)
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

	TextureManager::Instance()->ClearTextures();

	return TRUE;
}