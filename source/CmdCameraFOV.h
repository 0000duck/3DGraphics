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