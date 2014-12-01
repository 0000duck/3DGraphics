#ifndef INCLUDED_CMDNORMAL_H
#define INCLUDED_CMDNORMAL_H

#include "CmdCommand.h"

class CCmdNormal : public CCmdCommand
{
public:
	CCmdNormal(void) {}
	~CCmdNormal(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDNORMAL_H