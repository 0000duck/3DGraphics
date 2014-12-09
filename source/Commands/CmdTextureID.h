#ifndef INCLUDED_CMDTEXTUREID_H
#define INCLUDED_CMDTEXTUREID_H

#include "CmdCommand.h"

class CCmdTextureID : public CCmdCommand
{
public:
	CCmdTextureID(void) {}
	~CCmdTextureID(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDTEXTUREID_H