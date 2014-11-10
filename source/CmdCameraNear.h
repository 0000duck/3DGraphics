//====================================================================================================
//	File: CmdCameraNear.h
//	Created by: Tyler Staples
//	Date created: 8/11/2014
//	Description: 
//		Implementation of the "cameraNear" command.
//		Takes 1 parameter for the z-distance of the near clipping plane.
//====================================================================================================

#ifndef INCLUDED_CMDCAMERANEAR_H
#define INCLUDED_CMDCAMERANEAR_H

#include "CmdCommand.h"

class CCmdCameraNear : public CCmdCommand
{
public:
	CCmdCameraNear(void) {}
	~CCmdCameraNear(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDCAMERANEAR_H