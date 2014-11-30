//====================================================================================================
//	File: CmdWorldAmbient.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Implementaion of the "worldAmbient" command.
//		Takes 3 params (float) for the (r, g, b) values.
//		Sets the world ambient.
//====================================================================================================

#ifndef INCLUDED_CMDWORLDAMBIENT_H
#define INCLUDED_CMDWORLDAMBIENT_H

#include "CmdCommand.h"

class CCmdWorldAmbient : public CCmdCommand
{
public:
	CCmdWorldAmbient(void) {}
	~CCmdWorldAmbient(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDWORLDAMBIENT_H