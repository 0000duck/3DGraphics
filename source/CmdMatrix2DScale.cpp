#include "stdafx.h"
#include "CmdMatrix2DScale.h"
#include "MatrixManager.h"
#include "Vector2.h"
#include "ScriptParser.h"

BOOL CCmdMatrix2DScale::execute(CString &params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need 4 params for dimensions
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

	// Translate the current matrix
	MatrixManager::Instance()->Scale2D(sv);

	return TRUE;
}
