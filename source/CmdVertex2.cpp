#include "stdafx.h"
#include "CmdVertex2.h"
#include "ScriptParser.h"
#include "Rasterizer.h"
#include "PrimManager.h"
#include "StateManager.h"


BOOL CCmdVertex2::execute(CString &params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need at least 2 param for mode
	const int numParams = 2;
	if (paramStrList.GetCount() < numParams)
	{
		return FALSE;
	}

	CVertex2 vert;
	POSITION coord = paramStrList.GetHeadPosition();
	
	// Cast the x and y coords to floats and store them in the vertex
	CString paramStr = paramStrList.GetNext(coord);
	vert.point.x = (float)(wcstod(paramStr, NULL));
	paramStr = paramStrList.GetNext(coord);
	vert.point.y = (float)(wcstod(paramStr, NULL));

	// Get the current draw color from StateManager
	vert.color = StateManager::Instance()->GetColor();

	// Add the vertex to the current primitive
	PrimManager::Instance()->AddVertex(vert);

	return TRUE;
}
