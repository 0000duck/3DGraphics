#ifndef INCLUDED_CMDMATRIX3DIDENTITY_H
#define INCLUDED_CMDMATRIX3DIDENTITY_H

#include "CmdCommand.h"

class CCmdMatrix3DIdentity : public CCmdCommand
{
public:
	CCmdMatrix3DIdentity(void) {}
	~CCmdMatrix3DIdentity(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATRIX3DIDENTITY_H