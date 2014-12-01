#include "stdafx.h"
#include "CmdNormal.h"
#include "Utility/ScriptParser.h"
#include "Containers/Vector3.h"
#include "Graphics/PrimManager.h"

BOOL CCmdNormal::execute(CString &params)
{
	// Decode Parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need n params for dimensions
	const int numParams = 3;
	if (paramStrList.GetCount() != numParams)
	{
		return FALSE;
	}

	float args[numParams];
	CScriptParser::ToArray(paramStrList, numParams, args);
	CVector3 normal(args[0], args[1], args[2]);

	// Assume the values passed in aren't normalized; normalize them.
	normal.Normalize();

	PrimManager::Instance()->SetCurrentNormal(normal);

	return TRUE;
}