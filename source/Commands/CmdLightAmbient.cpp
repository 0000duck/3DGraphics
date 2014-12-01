#include "stdafx.h"
#include "CmdLightAmbient.h"
#include "Utility/ScriptParser.h"
#include "Containers/Color.h"
#include "Graphics/LightManager.h"

BOOL CCmdLightAmbient::execute(CString &params)
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
		LightManager::Instance()->SetMaterialColor(Material::Ambient, color);
	}

	return TRUE;
}