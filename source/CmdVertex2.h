//====================================================================================================
//	File: CmdVertex2.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Implementation of the "vertex2" command.
//		Takes 2 parameters for the x and y coordinates of the vertex.
//		Queries PrimManager to add the vertex to the current primitive.
//====================================================================================================

#ifndef INCLUDED_CMDVERTEX2_H
#define INCLUDED_CMDVERTEX2_H
#pragma once

#include "CmdCommand.h"

class CCmdVertex2 : public CCmdCommand
{
public:
	CCmdVertex2(void) {}
	~CCmdVertex2(void) {}

public:
	BOOL execute(CString &params);
};

#endif