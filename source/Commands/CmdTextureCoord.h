#ifndef INCLUDED_CMDTEXTURECOORD_H
#define INCLUDED_CMDTEXTURECOORD_H

#include "CmdCommand.h"

class CCmdTextureCoord : public CCmdCommand
{
public:
	CCmdTextureCoord(void) {}
	~CCmdTextureCoord(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDTEXTURECOORD_H