#include "stdafx.h"
#include "CmdDrawBegin.h"
#include "Utility/ScriptParser.h"
#include "Graphics/PrimManager.h"
#include "Graphics/StateManager.h"

BOOL CCmdDrawBegin::execute(CString &params)
{
	// Check that we can begin drawing
	if (StateManager::Instance()->IsDrawing())
	{
		return FALSE;
	}
	
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need at least 1 param for mode
	const int numParams = 1;
	if (paramStrList.GetCount() < numParams)
	{
		return FALSE;
	}

	// Check the primitive tpye is valid
	CString typestr = paramStrList.GetHead();
	int type = PrimType::CompareMode(typestr);
	if (PrimType::IsValid(type))
	{
		// Set the primitive type and tell PrimManager to add any
		// following verticies to this primitive.
		PrimManager::Instance()->CreatePrimitive(PrimType::Type(type));
		PrimManager::Instance()->EnableReading();

		// Tell Stateman that a begindraw call has been made
		StateManager::Instance()->StartDrawing();
	}

	return TRUE;
}
