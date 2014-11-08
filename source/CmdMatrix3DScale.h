#ifndef INCLUDED_CMDMATRIX3DSCALE_H
#define INCLUDED_CMDMATRIX3DSCALE_H

#include "CmdCommand.h"

class CCmdMatrix3DScale : public CCmdCommand
{
public:
	CCmdMatrix3DScale(void) {}
	~CCmdMatrix3DScale(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATRIX3DSCALE_H