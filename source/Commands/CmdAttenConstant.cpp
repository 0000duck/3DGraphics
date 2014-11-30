#include "stdafx.h"
#include "CmdAttenConstant.h"
#include "Utility/ScriptParser.h"
#include "Graphics/LightManager.h"

BOOL CCmdAttenConstant::execute(CString &params)
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
	LightManager::Instance()->SetAttenuation(LightType::Constant, f);

	return TRUE;
}