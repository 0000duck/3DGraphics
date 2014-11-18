//====================================================================================================
//	File: CmdBackfaceCull.h
//	Created by: Tyler Staples
//	Date created: 17/11/2014
//	Description: 
//		Implementaion of the "backfacecull" command.
//		Takes 1 parameter: "on" or "off" to enable/disable backface culling
//====================================================================================================

#ifndef INCLUDED_CMDBACKFACECULL_H
#define INCLUDED_CMDBACKFACECULL_H

#include "CmdCommand.h"

class CCmdBackfaceCull : public CCmdCommand
{
public:
	CCmdBackfaceCull(void) {}
	~CCmdBackfaceCull(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDBACKFACECULL_H