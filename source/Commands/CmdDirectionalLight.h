//====================================================================================================
//	File: CmdDirectionalLight.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Implementaion of the "directonalLight" command.
//		Takes 3 params (float) for the (x, y, z) normalized direction the light points in.
//		Creates a directional light pointing in the specified direction.
//====================================================================================================

#ifndef INCLUDED_CMDDIRECTIONALLIGHT_H
#define INCLUDED_CMDDIRECTIONALLIGHT_H

#include "CmdCommand.h"

class CCmdDirectionalLight : public CCmdCommand
{
public:
	CCmdDirectionalLight(void) {}
	~CCmdDirectionalLight(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDDIRECTIONALLIGHT_H