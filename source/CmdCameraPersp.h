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