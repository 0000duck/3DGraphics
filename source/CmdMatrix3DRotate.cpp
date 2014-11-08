#include "stdafx.h"
#include "CmdMatrix3DRotate.h"
#include "ScriptParser.h"
#include "MatrixManager.h"

BOOL CCmdMatrix3DRotate::execute(CString &params)
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
	float deg = (float)(wcstod(paramStr, NULL));
	MatrixManager::Instance()->Rotate3D(deg);

	return TRUE;
}