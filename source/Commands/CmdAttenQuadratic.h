//====================================================================================================
//	File: CmdAttenQuadratic.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Implementaion of the "attenQuadratic" command.
//		Takes a single param (float) for the value.
//		Sets the current quadratic attenuation factor.
//====================================================================================================

#ifndef INCLUDED_CMDATTENQUADRATIC_H
#define INCLUDED_CMDATTENQUADRATIC_H

#include "CmdCommand.h"

class CCmdAttenQuadratic : public CCmdCommand
{
public:
	CCmdAttenQuadratic(void) {}
	~CCmdAttenQuadratic(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDATTENQUADRATIC_H