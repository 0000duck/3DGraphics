//====================================================================================================
//	File: CmdMatrix2DRotate.h
//	Created by: Tyler Staples
//	Date created: 05/11/2014
//	Description: 
//		Implementaion of the "matrix2DRotate" command.
//		Takes 1 parameter for the number of degrees to rotate by in the Z axis.
//		Applies this rotation to the matrix in MatrixManager
//====================================================================================================

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