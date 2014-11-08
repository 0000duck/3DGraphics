#ifndef INCLUDED_CMDMATRIX3DTRANSLATE_H
#define INCLUDED_CMDMATRIX3DTRANSLATE_H

#include "CmdCommand.h"

class CCmdMatrix3DTranslate : public CCmdCommand
{
public:
	CCmdMatrix3DTranslate(void) {}
	~CCmdMatrix3DTranslate(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATRIX3DTRANSLATE_H