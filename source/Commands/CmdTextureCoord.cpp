#include "stdafx.h"
#include "CmdTextureCoord.h"
#include "Utility/ScriptParser.h"
#include "Graphics/PrimManager.h"

BOOL CCmdTextureCoord::execute(CString &params)
{
	// Decode Parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need n params for dimensions
	const int numParams = 2;
	if (paramStrList.GetCount() != numParams)
	{
		return FALSE;
	}

	float coords[numParams];
	CScriptParser::ToArray(paramStrList, numParams, coords);
	PrimManager::Instance()->SetTexturingEnabled(true);
	PrimManager::Instance()->SetCurrentTexCoord(CVector2(coords[0], coords[1]));

	return TRUE;
}