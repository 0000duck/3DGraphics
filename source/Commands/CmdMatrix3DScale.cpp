#include "stdafx.h"
#include "CmdMatrix3DScale.h"
#include "Utility/ScriptParser.h"
#include "Containers/Vector3.h"
#include "Graphics/MatrixManager.h"

BOOL CCmdMatrix3DScale::execute(CString &params)
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

	MatrixManager::Instance()->Scale3D(sv);

	return TRUE;
}