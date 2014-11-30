#include "stdafx.h"
#include "CmdDirectionalLight.h"
#include "Utility/ScriptParser.h"
#include "Graphics/LightManager.h"
#include "Lighting/DirectionalLight.h"

BOOL CCmdDirectionalLight::execute(CString &params)
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
	CVector3 direction(args[0], args[1], args[2]);

	CDirectionalLight* light = new CDirectionalLight(direction);
	LightManager::Instance()->AddLight(light);

	return TRUE;
}