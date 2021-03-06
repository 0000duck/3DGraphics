#include "stdafx.h"
#include "CmdLightDiffuse.h"
#include "Utility/ScriptParser.h"
#include "Containers/Color.h"
#include "Graphics/LightManager.h"

BOOL CCmdLightDiffuse::execute(CString &params)
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

	if (color.IsValid())
	{
		LightManager::Instance()->SetMaterialColor(Material::Diffuse, color);
	}

	return TRUE;
}