#include "stdafx.h"
#include "CmdCameraFar.h"
#include "ScriptParser.h"
#include "Camera.h"

BOOL CCmdCameraFar::execute(CString &params)
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

	CString paramStr = paramStrList.GetHead();
	float f = (float)(wcstod(paramStr, NULL));

	Camera::Instance()->SetFar(f);

	return TRUE;
}