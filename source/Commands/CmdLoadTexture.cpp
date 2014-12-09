#include "stdafx.h"
#include "CmdLoadTexture.h"
#include "Utility/ScriptParser.h"
#include "Graphics/TextureManager.h"

BOOL CCmdLoadTexture::execute(CString &params)
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

	POSITION pos = paramStrList.GetHeadPosition();
	CString paramStr = paramStrList.GetHead();
	int id = (int)(wcstod(paramStr, NULL));
	
	paramStr = paramStrList.GetNext(pos);
	TextureManager::Instance()->LoadTexture(id, paramStr);

	return TRUE;
}