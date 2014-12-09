#ifndef INCLUDED_CMDCLEARTEXTURES_H
#define INCLUDED_CMDCLEARTEXTURES_H

#include "CmdCommand.h"

class CCmdClearTextures : public CCmdCommand
{
public:
	CCmdClearTextures(void) {}
	~CCmdClearTextures(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDCLEARTEXTURES_H