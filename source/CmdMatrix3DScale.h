//====================================================================================================
//	File: CmdMatrix3DScale.h
//	Created by: Tyler Staples
//	Date created: 7/11/2014
//	Description: 
//		Implementation of the "matrix3DScale" command.
//		Combines a scaling matrix with the current transformation matrix.
//		Takes 3 parameters for the amount to scale in each axis.
//====================================================================================================

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