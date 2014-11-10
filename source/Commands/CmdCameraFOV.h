//====================================================================================================
//	File: CmdCameraFOV.h
//	Created by: Tyler Staples
//	Date created: 8/11/2014
//	Description: 
//		Implementation of the "cameraFOV" command.
//		Takes 1 parameter for the field-of-view in degrees.
//====================================================================================================

#ifndef INCLUDED_CMDCAMERAFOV_H
#define INCLUDED_CMDCAMERAFOV_H

#include "CmdCommand.h"

class CCmdCameraFOV : public CCmdCommand
{
public:
	CCmdCameraFOV(void) {}
	~CCmdCameraFOV(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDCAMERAFOV_H