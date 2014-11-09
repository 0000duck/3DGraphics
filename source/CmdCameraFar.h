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