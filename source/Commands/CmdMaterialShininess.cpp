#include "stdafx.h"
#include "CmdMaterialShininess.h"
#include "Utility/ScriptParser.h"
#include "Graphics/PrimManager.h"

BOOL CCmdMaterialShininess::execute(CString &params)
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
	float shine = (float)(wcstod(paramStr, NULL));
	PrimManager::Instance()->SetMaterialShine(shine);

	return TRUE;
}