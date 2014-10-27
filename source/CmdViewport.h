// ----------------------------------------------------------------------------
//	File: CmdViewport.h
//	Created by: Tyler Staples
//	Date created: 26/10/2014
//	Description: 
//		Implementaion of the "viewport" command.
//		Takes a 4 parameters for top left (x,y) and bottom right (x,y) coordinates.
//		Defines the dimensions of a rectangular viewport.
// ----------------------------------------------------------------------------

#ifndef INCLUDED_CMDVIEWPORT_H
#define INCLUDED_CMDVIEWPORT_H
#pragma once

#include "CmdCommand.h"

class CCmdViewport : public CCmdCommand
{
public:
	CCmdViewport(void) {}
	~CCmdViewport(void) {}

public:
	BOOL execute(CString &params);
};

#endif