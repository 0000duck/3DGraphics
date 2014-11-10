//====================================================================================================
//	File: CmdClip.h
//	Created by: Tyler Staples
//	Date created: 26/10/2014
//	Description: 
//		Implementaion of the "clip" command.
//		Takes 1 parameter: "on" or "off" to enable/disable clipping
//====================================================================================================

#ifndef INCLUDED_CMDCLIP_H
#define INCLUDED_CMDCLIP_H
#pragma once

#include "CmdCommand.h"

class CCmdClip : public CCmdCommand
{
public:
	CCmdClip(void) {}
	~CCmdClip(void) {}

public:
	BOOL execute(CString &params);
};

#endif