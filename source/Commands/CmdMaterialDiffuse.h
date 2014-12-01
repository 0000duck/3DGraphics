#ifndef INCLUDED_CMDMATERIALDIFFUSE_H
#define INCLUDED_CMDMATERIALDIFFUSE_H

#include "CmdCommand.h"

class CCmdMaterialDiffuse : public CCmdCommand
{
public:
	CCmdMaterialDiffuse(void) {}
	~CCmdMaterialDiffuse(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATERIALDIFFUSE_H