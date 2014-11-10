//====================================================================================================
//	File: CmdDrawEnd.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Implementation of the "drawend" command.
//		Tells PrimManager to draw all primitives it is currently holding.
//====================================================================================================

#ifndef INCLUDED_CMDDRAWEND_H
#define INCLUDED_CMDDRAWEND_H
#pragma once

#include "CmdCommand.h"

class CCmdDrawEnd : public CCmdCommand
{
public:
	CCmdDrawEnd(void) {}
	~CCmdDrawEnd(void) {}

public:
	BOOL execute(CString &params);
};

#endif