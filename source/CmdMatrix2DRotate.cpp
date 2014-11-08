#include "stdafx.h"
#include "CmdMatrix2DRotate.h"
#include "MatrixManager.h"
#include "ScriptParser.h"

BOOL CCmdMatrix2DRotate::execute(CString &params)
{
	// Decode Parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need 1 params for degrees to rotate by
	const int numParams = 1;
	if (paramStrList.GetCount() != numParams)
	{
		return FALSE;
	}

	CString paramStr = paramStrList.GetHead();
	float deg = (float)(wcstod(paramStr, NULL));
	MatrixManager::Instance()->Rotate2D(deg);

	return TRUE;
}