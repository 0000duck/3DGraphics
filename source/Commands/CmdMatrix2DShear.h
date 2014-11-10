//====================================================================================================
//	File: CmdMatrix2DShear.h
//	Created by: Tyler Staples
//	Date created: 05/11/2014
//	Description: 
//		Implementaion of the "matrix2DShear" command.
//		Takes 2 parameters for the amount to shear by in the x and y axes.
//		Applies this shear to the matrix in MatrixManager
//====================================================================================================

#ifndef INCLUDED_CMDMATRIX2DSHEAR_H
#define INCLUDED_CMDMATRIX2DSHEAR_H

#include "CmdCommand.h"

class CCmdMatrix2DShear : public CCmdCommand
{
public:
	CCmdMatrix2DShear(void) {}
	~CCmdMatrix2DShear(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATRIX2DSHEAR_H