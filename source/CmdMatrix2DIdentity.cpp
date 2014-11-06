#include "stdafx.h"
#include "CmdMatrix2DIdentity.h"
#include "MatrixManager.h"
#include "ScriptParser.h"

BOOL CCmdMatrix2DIdentity::execute(CString &params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need 4 params for dimensions
	const int numParams = 0;
	if (paramStrList.GetCount() != numParams)
	{
		return FALSE;
	}

	// Load an identity matrix
	MatrixManager::Instance()->LoadIdentity();

	return TRUE;
}
