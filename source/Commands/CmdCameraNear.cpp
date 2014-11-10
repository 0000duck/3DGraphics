#include "stdafx.h"
#include "CmdCameraNear.h"
#include "Utility/ScriptParser.h"
#include "Graphics/Camera.h"

BOOL CCmdCameraNear::execute(CString &params)
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
	float n = (float)(wcstod(paramStr, NULL));

	Camera::Instance()->SetNear(n);

	return TRUE;
}