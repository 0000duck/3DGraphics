#include "stdafx.h"
#include "CmdAttenQuadratic.h"
#include "Utility/ScriptParser.h"
#include "Graphics/LightManager.h"

BOOL CCmdAttenQuadratic::execute(CString &params)
{
	// Decode Parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need n params for dimensions
	const int numParams = 1;
	if (paramStrList.GetCount() != numParams)
	{
		return FALSE;
	}

	CString paramStr = paramStrList.GetHead();
	float f = (float)(wcstod(paramStr, NULL));
	LightManager::Instance()->SetAttenuation(LightType::Quadratic, f);

	return TRUE;
}