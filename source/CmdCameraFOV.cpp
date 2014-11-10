#include "stdafx.h"
#include "CmdCameraFOV.h"
#include "ScriptParser.h"
#include "Camera.h"

BOOL CCmdCameraFOV::execute(CString &params)
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
	float deg = (float)(wcstod(paramStr, NULL));

	Camera::Instance()->SetFOV(deg);

	return TRUE;
}