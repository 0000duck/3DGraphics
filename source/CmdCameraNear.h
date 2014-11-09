#ifndef INCLUDED_CMDCAMERANEAR_H
#define INCLUDED_CMDCAMERANEAR_H

#include "CmdCommand.h"

class CCmdCameraNear : public CCmdCommand
{
public:
	CCmdCameraNear(void) {}
	~CCmdCameraNear(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDCAMERANEAR_H