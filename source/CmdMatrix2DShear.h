#ifndef INCLUDED_CMDMATRIX2DSHEAR_H
#define INCLUDED_CMDMATRIX2DSHEAR_H

#include "CmdCommand.h"

class CCmdMatrix2DShear : public CCmdCommand
{
public:
	CCmdMatrix2DShear(void) {}
	~CCmdMatrix2DShear(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATRIX2DSHEAR_H