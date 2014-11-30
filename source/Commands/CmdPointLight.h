//====================================================================================================
//	File: CmdPointlLight.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Implementaion of the "pointLight" command.
//		Takes 3 params (float) for the (x, y, z) position of the light.
//		Creates a point light pointing in the specified location.
//====================================================================================================

#ifndef INCLUDED_CMDPOINTLIGHT_H
#define INCLUDED_CMDPOINTLIGHT_H

#include "CmdCommand.h"

class CCmdPointLight : public CCmdCommand
{
public:
	CCmdPointLight(void) {}
	~CCmdPointLight(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDPOINTLIGHT_H