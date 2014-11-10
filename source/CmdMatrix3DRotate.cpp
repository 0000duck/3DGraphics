#include "stdafx.h"
#include "CmdMatrix3DRotate.h"
#include "ScriptParser.h"
#include "MatrixManager.h"
#include "Vector3.h"

BOOL CCmdMatrix3DRotate::execute(CString &params)
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

	
	float rots[numParams];
	CScriptParser::ToArray(paramStrList, numParams, rots);
	CVector3 rot(rots[0], rots[1], rots[2]);
	MatrixManager::Instance()->Rotate3D(rot);

	return TRUE;
}