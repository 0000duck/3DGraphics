#ifndef INCLUDED_CMDSHADINGMODE_H
#define INCLUDED_CMDSHADINGMODE_H

#include "CmdCommand.h"

class CCmdShadingMode : public CCmdCommand
{
public:
	CCmdShadingMode(void) {}
	~CCmdShadingMode(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDSHADINGMODE_H