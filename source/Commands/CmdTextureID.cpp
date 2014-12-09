#include "stdafx.h"
#include "CmdTextureID.h"
#include "Utility/ScriptParser.h"
#include "Graphics/PrimManager.h"

BOOL CCmdTextureID::execute(CString &params)
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

	CString paramStr = paramStrList.GetHead();
	int id = (int)(wcstod(paramStr, NULL));
	PrimManager::Instance()->SetTexturingEnabled(true);
	PrimManager::Instance()->SetCurrentTexture(id);

	return TRUE;
}