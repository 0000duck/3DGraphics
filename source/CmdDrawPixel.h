#ifndef INCLUDED_CMDDRAWPIXEL_H
#define INCLUDED_CMDDRAWPIXEL_H

#pragma once
#include "CmdCommand.h"

class CCmdDrawPixel : public CCmdCommand
{
public:
	CCmdDrawPixel(void) {}
	~CCmdDrawPixel(void) {}

public:
	BOOL execute( CString &params );
};

#endif