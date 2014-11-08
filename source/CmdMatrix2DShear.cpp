#include "stdafx.h"
#include "CmdMatrix2DShear.h"
#include "ScriptParser.h"
#include "MatrixManager.h"
#include "Vector2.h"

BOOL CCmdMatrix2DShear::execute(CString &params)
{
	// Decode Parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need n params for dimensions
	const int numParams = 2;
	if (paramStrList.GetCount() != numParams)
	{
		return FALSE;
	}

	CVector2 sv;
	POSITION scale = paramStrList.GetHeadPosition();
	
	// Cast the x and y coords to floats and store them in the vector
	CString paramStr = paramStrList.GetNext(scale);
	sv.x = (float)(wcstod(paramStr, NULL));
	paramStr = paramStrList.GetNext(scale);
	sv.y = (float)(wcstod(paramStr, NULL));

	MatrixManager::Instance()->Shear2D(sv);

	return TRUE;
}