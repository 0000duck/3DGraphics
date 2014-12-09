#ifndef INCLUDED_CMDTEXTUREBOUNDARY_H
#define INCLUDED_CMDTEXTUREBOUNDARY_H

#include "CmdCommand.h"

class CCmdTextureBoundary : public CCmdCommand
{
public:
	CCmdTextureBoundary(void) {}
	~CCmdTextureBoundary(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDTEXTUREBOUNDARY_H