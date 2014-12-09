#ifndef INCLUDED_CMDLOADTEXTURE_H
#define INCLUDED_CMDLOADTEXTURE_H

#include "CmdCommand.h"

class CCmdLoadTexture : public CCmdCommand
{
public:
	CCmdLoadTexture(void) {}
	~CCmdLoadTexture(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDLOADTEXTURE_H