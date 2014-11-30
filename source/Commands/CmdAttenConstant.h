//====================================================================================================
//	File: CmdAttenConstant.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Implementaion of the "attenConstant" command.
//		Takes a single param (float) for the value.
//		Sets the current constant attenuation factor.
//====================================================================================================

#ifndef INCLUDED_CMDATTENCONSTANT_H
#define INCLUDED_CMDATTENCONSTANT_H

#include "CmdCommand.h"

class CCmdAttenConstant : public CCmdCommand
{
public:
	CCmdAttenConstant(void) {}
	~CCmdAttenConstant(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDATTENCONSTANT_H