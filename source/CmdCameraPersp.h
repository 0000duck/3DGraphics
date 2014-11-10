//====================================================================================================
//	File: CmdCameraPersp.h
//	Created by: Tyler Staples
//	Date created: 8/11/2014
//	Description: 
//		Implementation of the "cameraPersp" command.
//		Takes 6 parameter for the (x,y,z) of the camera's origin, and the (x,y,z) of
//		what the camera is looking at.
//====================================================================================================

#ifndef INCLUDED_CMDCAMERAPERSP_H
#define INCLUDED_CMDCAMERAPERSP_H

#include "CmdCommand.h"

class CCmdCameraPersp : public CCmdCommand
{
public:
	CCmdCameraPersp(void) {}
	~CCmdCameraPersp(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDCAMERAPERSP_H