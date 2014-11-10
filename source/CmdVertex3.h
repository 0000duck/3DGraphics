//====================================================================================================
//	File: CmdVertex3.h
//	Created by: Tyler Staples
//	Date created: 5/11/2014
//	Description: 
//		Implementation of the "vertex3" command.
//		Takes 3 parameters for the x, y, z coordinates of the vertex.
//====================================================================================================

#ifndef INCLUDED_CMDVERTEX3_H
#define INCLUDED_CMDVERTEX3_H

#include "CmdCommand.h"

class CCmdVertex3 : public CCmdCommand
{
public:
	CCmdVertex3(void) {}
	~CCmdVertex3(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDVERTEX3_H