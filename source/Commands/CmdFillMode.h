//====================================================================================================
//	File: CmdFillMode.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Implementation of the "fillmode" command.
//		Takes a single parameter for the desired fill mode which dictates
//		how the primitives are drawn.
//====================================================================================================

#ifndef INCLUDED_CMDFILLMODE_H
#define INCLUDED_CMDFILLMODE_H
#pragma once

#include "CmdCommand.h"

class CCmdFillMode : public CCmdCommand
{
public:
	CCmdFillMode(void) {}
	~CCmdFillMode(void) {}

public:
	BOOL execute(CString &params);
};

#endif