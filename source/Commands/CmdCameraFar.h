//====================================================================================================
//	File: CmdCameraFar.h
//	Created by: Tyler Staples
//	Date created: 8/11/2014
//	Description: 
//		Implementation of the "cameraFar" command.
//		Takes 1 parameter for the z-distance of the far clipping plane.
//====================================================================================================

#ifndef INCLUDED_CMDCAMERAFAR_H
#define INCLUDED_CMDCAMERAFAR_H

#include "CmdCommand.h"

class CCmdCameraFar : public CCmdCommand
{
public:
	CCmdCameraFar(void) {}
	~CCmdCameraFar(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDCAMERAFAR_H