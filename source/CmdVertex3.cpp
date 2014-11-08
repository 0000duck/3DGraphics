#include "stdafx.h"
#include "CmdVertex3.h"
#include "ScriptParser.h"
#include "Vertex3.h"
#include "PrimManager.h"
#include "StateManager.h"

BOOL CCmdVertex3::execute(CString &params)
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

	CVertex3 vert;
	POSITION coord = paramStrList.GetHeadPosition();
	
	// Cast the x and y coords to floats and store them in the vertex
	CString paramStr = paramStrList.GetNext(coord);
	vert.point.x = (float)(wcstod(paramStr, NULL));
	paramStr = paramStrList.GetNext(coord);
	vert.point.y = (float)(wcstod(paramStr, NULL));
	paramStr = paramStrList.GetNext(coord);
	vert.point.z = (float)(wcstod(paramStr, NULL));
	vert.point.w = 1.0f;

	// Get the current draw color from StateManager
	vert.color = StateManager::Instance()->GetColor();

	// Add the vertex to the current primitive
	PrimManager::Instance()->AddVertex(vert);

	return TRUE;
}