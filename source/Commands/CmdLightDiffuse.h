//====================================================================================================
//	File: CmdLightDiffuse.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Implementaion of the "lightDiffuse" command.
//		Takes 3 params (float) for the (r, g, b) values.
//		Sets the current diffuse.
//====================================================================================================

#ifndef INCLUDED_CMDLIGHTDIFFUSE_H
#define INCLUDED_CMDLIGHTDIFFUSE_H

#include "CmdCommand.h"

class CCmdLightDiffuse : public CCmdCommand
{
public:
	CCmdLightDiffuse(void) {}
	~CCmdLightDiffuse(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDLIGHTDIFFUSE_H