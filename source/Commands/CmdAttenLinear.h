//====================================================================================================
//	File: CmdAttenLinear.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Implementaion of the "attenLinear" command.
//		Takes a single param (float) for the value.
//		Sets the current linear attenuation factor.
//====================================================================================================

#ifndef INCLUDED_CMDATTENLINEAR_H
#define INCLUDED_CMDATTENLINEAR_H

#include "CmdCommand.h"

class CCmdAttenLinear : public CCmdCommand
{
public:
	CCmdAttenLinear(void) {}
	~CCmdAttenLinear(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDATTENLINEAR_H