#ifndef INCLUDED_CMDZBUFFER_H
#define INCLUDED_CMDZBUFFER_H

#include "CmdCommand.h"

class CCmdZBuffer : public CCmdCommand
{
public:
	CCmdZBuffer(void) {}
	~CCmdZBuffer(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDZBUFFER_H