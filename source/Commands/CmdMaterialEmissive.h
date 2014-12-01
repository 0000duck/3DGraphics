#ifndef INCLUDED_CMDMATERIALEMISSIVE_H
#define INCLUDED_CMDMATERIALEMISSIVE_H

#include "CmdCommand.h"

class CCmdMaterialEmissive : public CCmdCommand
{
public:
	CCmdMaterialEmissive(void) {}
	~CCmdMaterialEmissive(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATERIALEMISSIVE_H