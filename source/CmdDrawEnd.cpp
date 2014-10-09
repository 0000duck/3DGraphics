#include "stdafx.h"
#include "CmdDrawEnd.h"
#include "ScriptParser.h"
#include "Rasterizer.h"
#include "PrimManager.h"
#include "StateManager.h"


BOOL CCmdDrawEnd::execute(CString &params)
{
	// If we aren't drawing, then there is no drawing to end
	if (!StateManager::Instance()->IsDrawing())
	{
		return FALSE;
	}
	
	// Don't accept any more verticies
	PrimManager::Instance()->DisableReading();

	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need at least 1 param for mode
	const int numParams = 0;
	if (paramStrList.GetCount() < numParams)
	{
		return FALSE;
	}

	// Tell PrimManager to draw all the primitives in its list
	PrimManager::Instance()->DrawAll();

	// Tell stateman that we are finished drawing
	StateManager::Instance()->StopDrawing();

	return TRUE;
}
