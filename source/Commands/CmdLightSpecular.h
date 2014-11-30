//====================================================================================================
//	File: CmdLightSpecular.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Implementaion of the "lightSpecualr" command.
//		Takes 3 params (float) for the (r, g, b) values.
//		Sets the current specular.
//====================================================================================================

#ifndef INCLUDED_CMDLIGHTSPECULAR_H
#define INCLUDED_CMDLIGHTSPECULAR_H

#include "CmdCommand.h"

class CCmdLightSpecular : public CCmdCommand
{
public:
	CCmdLightSpecular(void) {}
	~CCmdLightSpecular(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDLIGHTSPECULAR_H