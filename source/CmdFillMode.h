// ----------------------------------------------------------------------------
//	File: CmdFillMode.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Sets the draw color.
// ----------------------------------------------------------------------------

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