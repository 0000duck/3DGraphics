#include "stdafx.h"
#include "CmdPointLight.h"
#include "Utility/ScriptParser.h"
#include "Graphics/LightManager.h"
#include "Lighting/PointLight.h"

BOOL CCmdPointLight::execute(CString &params)
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

	float args[numParams];
	CScriptParser::ToArray(paramStrList, numParams, args);
	CVector3 position(args[0], args[1], args[2]);

	// Init atten values to the current ones in LightManager
	CPointLight* light = new CPointLight(position);
	light->SetAttenConstant(LightManager::Instance()->GetAttenConstant());
	light->SetAttenLinear(LightManager::Instance()->GetAttenLinear());
	light->SetAttenQuadratic(LightManager::Instance()->GetAttenQuadratic());

	light->SetAmbient(LightManager::Instance()->GetAmbient());
	light->SetDiffuse(LightManager::Instance()->GetDiffuse());
	light->SetSpecular(LightManager::Instance()->GetSpecular());

	LightManager::Instance()->AddLight(light);

	return TRUE;
}