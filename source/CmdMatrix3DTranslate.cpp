#include "stdafx.h"
#include "CmdMatrix3DTranslate.h"
#include "ScriptParser.h"
#include "Vector3.h"
#include "MatrixManager.h"

BOOL CCmdMatrix3DTranslate::execute(CString &params)
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

	CVector3 sv;
	POSITION scale = paramStrList.GetHeadPosition();
	
	CString paramStr = paramStrList.GetNext(scale);
	sv.x = (float)(wcstod(paramStr, NULL));
	paramStr = paramStrList.GetNext(scale);
	sv.y = (float)(wcstod(paramStr, NULL));
	paramStr = paramStrList.GetNext(scale);
	sv.z = (float)(wcstod(paramStr, NULL));

	MatrixManager::Instance()->Translate3D(sv);

	return TRUE;
}