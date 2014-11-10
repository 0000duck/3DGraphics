#include "stdafx.h"
#include "CmdCameraPersp.h"
#include "Utility/ScriptParser.h"
#include "Graphics/Camera.h"

BOOL CCmdCameraPersp::execute(CString &params)
{
	// Decode Parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need n params for dimensions
	const int numParams = 6;
	if (paramStrList.GetCount() < numParams)
	{
		return FALSE;
	}

	float args[numParams];
	CScriptParser::ToArray(paramStrList, numParams, args);

	CVector3 origin(args[0], args[1], args[2]);
	CVector3 interest(args[3], args[4], args[5]);
	Camera::Instance()->Create(origin, interest);

	return TRUE;
}