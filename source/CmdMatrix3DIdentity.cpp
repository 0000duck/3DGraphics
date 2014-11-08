#include "stdafx.h"
#include "CmdMatrix3DIdentity.h"
#include "ScriptParser.h"
#include "MatrixManager.h"

BOOL CCmdMatrix3DIdentity::execute(CString &params)
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

	// Load an identity matrix
	MatrixManager::Instance()->LoadIdentity3D();

	return TRUE;
}