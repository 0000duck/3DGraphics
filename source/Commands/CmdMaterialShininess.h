#ifndef INCLUDED_CMDMATERIALSHININESS_H
#define INCLUDED_CMDMATERIALSHININESS_H

#include "CmdCommand.h"

class CCmdMaterialShininess : public CCmdCommand
{
public:
	CCmdMaterialShininess(void) {}
	~CCmdMaterialShininess(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATERIALSHININESS_H