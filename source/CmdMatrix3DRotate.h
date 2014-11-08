#ifndef INCLUDED_CMDMATRIX3DROTATE_H
#define INCLUDED_CMDMATRIX3DROTATE_H

#include "CmdCommand.h"

class CCmdMatrix3DRotate : public CCmdCommand
{
public:
	CCmdMatrix3DRotate(void) {}
	~CCmdMatrix3DRotate(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATRIX3DROTATE_H