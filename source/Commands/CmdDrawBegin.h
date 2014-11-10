//====================================================================================================
//	File: CmdDrawBegin.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Implementaion of the "drawbegin" command.
//		Takes a single parameter for the primitive type to be drawn.
//		Tells PrimManager to accept any verticies that are read in.
//====================================================================================================

#ifndef INCLUDED_CMDDRAWBEGIN_H
#define INCLUDED_CMDDRAWBEGIN_H
#pragma once

#include "CmdCommand.h"

class CCmdDrawBegin : public CCmdCommand
{
public:
	CCmdDrawBegin(void) {}
	~CCmdDrawBegin(void) {}

public:
	BOOL execute(CString &params);
};

#endif