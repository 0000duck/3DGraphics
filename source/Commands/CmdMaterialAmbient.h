#ifndef INCLUDED_CMDMATERIALAMBIENT_H
#define INCLUDED_CMDMATERIALAMBIENT_H

#include "CmdCommand.h"

class CCmdMaterialAmbient : public CCmdCommand
{
public:
	CCmdMaterialAmbient(void) {}
	~CCmdMaterialAmbient(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATERIALAMBIENT_H