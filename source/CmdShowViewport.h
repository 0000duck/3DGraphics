//====================================================================================================
//	File: CmdShowViewport.h
//	Created by: Tyler Staples
//	Date created: 26/10/2014
//	Description: 
//		Implementaion of the "showviewport" command.
//		Takes 1 parameter: "on" or "off" to enable/disable drawing of the viewport
//====================================================================================================

#ifndef INCLUDED_CMDSHOWVIEWPORT_H
#define INCLUDED_CMDSHOWVIEWPORT_H
#pragma once

#include "CmdCommand.h"

class CCmdShowViewport : public CCmdCommand
{
public:
	CCmdShowViewport(void) {}
	~CCmdShowViewport(void) {}

public:
	BOOL execute(CString &params);
};

#endif