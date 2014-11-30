//====================================================================================================
//	File: CmdLightAmbient.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Implementaion of the "lightAmbient" command.
//		Takes 3 params (float) for the (r, g, b) values.
//		Sets the current ambient.
//====================================================================================================

#ifndef INCLUDED_CMDLIGHTAMBIENT_H
#define INCLUDED_CMDLIGHTAMBIENT_H

#include "CmdCommand.h"

class CCmdLightAmbient : public CCmdCommand
{
public:
	CCmdLightAmbient(void) {}
	~CCmdLightAmbient(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDLIGHTAMBIENT_H