//====================================================================================================
//	File: CmdMatrix3DRotate.h
//	Created by: Tyler Staples
//	Date created: 7/11/2014
//	Description: 
//		Implementation of the "matrix3DRotate" command.
//		Combines a rotation matrix with the current transformation matrix.
//		Takes 3 parameters for the degrees to rotate in the x,y,z axes.
//====================================================================================================

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