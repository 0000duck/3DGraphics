#include "stdafx.h"
#include "CmdMaterialSpecular.h"
#include "Utility/ScriptParser.h"
#include "Graphics/PrimManager.h"

BOOL CCmdMaterialSpecular::execute(CString &params)
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
	CColor color(args[0], args[1], args[2]);

	PrimManager::Instance()->SetMaterial(Material::Specular, color);

	return TRUE;
}