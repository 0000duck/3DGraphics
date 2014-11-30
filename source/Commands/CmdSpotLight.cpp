#include "stdafx.h"
#include "CmdSpotLight.h"
#include "Utility/ScriptParser.h"
#include "Graphics/LightManager.h"
#include "Lighting/SpotLight.h"

BOOL CCmdSpotLight::execute(CString &params)
{
	// Decode Parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need n params for dimensions
	const int numParams = 8;
	if (paramStrList.GetCount() != numParams)
	{
		return FALSE;
	}

	float args[numParams];
	CScriptParser::ToArray(paramStrList, numParams, args);
	CVector3 position(args[0], args[1], args[2]);
	CVector3 direction(args[3], args[4], args[5]);
	float angle = args[6];
	float decay = args[7];

	CSpotLight* light = new CSpotLight(position, direction, angle, decay);
	light->SetAttenConstant(LightManager::Instance()->GetAttenConstant());
	light->SetAttenLinear(LightManager::Instance()->GetAttenLinear());
	light->SetAttenQuadratic(LightManager::Instance()->GetAttenQuadratic());

	light->SetAmbient(LightManager::Instance()->GetAmbient());
	light->SetDiffuse(LightManager::Instance()->GetDiffuse());
	light->SetSpecular(LightManager::Instance()->GetSpecular());

	LightManager::Instance()->AddLight(light);

	return TRUE;
}