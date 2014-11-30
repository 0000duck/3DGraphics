//====================================================================================================
//	File: CmdClearLights.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Implementaion of the "clearLights" command.
//		Takes zero params.
//		Clears the global light list.
//====================================================================================================

#ifndef INCLUDED_CMDCLEARLIGHTS_H
#define INCLUDED_CMDCLEARLIGHTS_H

#include "CmdCommand.h"

class CCmdClearLights : public CCmdCommand
{
public:
	CCmdClearLights(void) {}
	~CCmdClearLights(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDCLEARLIGHTS_H