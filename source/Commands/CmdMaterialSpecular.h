#ifndef INCLUDED_CMDMATERIALSPECULAR_H
#define INCLUDED_CMDMATERIALSPECULAR_H

#include "CmdCommand.h"

class CCmdMaterialSpecular : public CCmdCommand
{
public:
	CCmdMaterialSpecular(void) {}
	~CCmdMaterialSpecular(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATERIALSPECULAR_H