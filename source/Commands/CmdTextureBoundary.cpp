#include "stdafx.h"
#include "CmdTextureBoundary.h"
#include "Utility/ScriptParser.h"
#include "Graphics/TextureManager.h"

BOOL CCmdTextureBoundary::execute(CString &params)
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

	POSITION pos = paramStrList.GetHeadPosition();
	CString paramStr = paramStrList.GetHead();
	int id = (int)(wcstod(paramStr, NULL));
	
	CString ustr = paramStrList.GetNext(pos);
	CString vstr = paramStrList.GetNext(pos);
	int U = GetTypeIndex(ustr, Texturing::ModeString, Texturing::NumModes);
	int V = GetTypeIndex(vstr, Texturing::ModeString, Texturing::NumModes);

	TextureManager::Instance()->SetTextureBoundary(id, Texturing::Boundary(U), Texturing::Boundary(V));

	return TRUE;
}