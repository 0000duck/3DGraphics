#ifndef INCLUDED_CMDVERTEX3_H
#define INCLUDED_CMDVERTEX3_H

#include "CmdCommand.h"

class CCmdVertex3 : public CCmdCommand
{
public:
	CCmdVertex3(void) {}
	~CCmdVertex3(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDVERTEX3_H