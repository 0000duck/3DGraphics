#ifndef INCLUDED_CMDMATRIX2DROTATE_H
#define INCLUDED_CMDMATRIX2DROTATE_H

#include "CmdCommand.h"

class CCmdMatrix2DRotate : public CCmdCommand
{
public:
	CCmdMatrix2DRotate(void) {}
	~CCmdMatrix2DRotate(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATRIX2DROTATE_H