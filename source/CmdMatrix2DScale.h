//====================================================================================================
//	File: CmdMatrix2DScale.h
//	Created by: Tyler Staples
//	Date created: 05/11/2014
//	Description: 
//		Implementaion of the "matrix2DScale" command.
//		Takes 2 parameters for the amount scaled by in the x and y axes.
//		Applies this scaling to the matrix in MatrixManager
//====================================================================================================

#ifndef INCLUDED_CMDMATRIX2DSCALE_H
#define INCLUDED_CMDMATRIX2DSCALE_H
#pragma once

#include "CmdCommand.h"

class CCmdMatrix2DTranslate : public CCmdCommand
{
public:
	CCmdMatrix2DTranslate(void) {}
	~CCmdMatrix2DTranslate(void) {}

public:
	BOOL execute(CString &params);
};

#endif // #ifndef INCLUDED_CMDMATRIX2DTRANSLATE_H