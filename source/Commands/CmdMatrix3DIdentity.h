//====================================================================================================
//	File: CmdMatrix3DIdentity.h
//	Created by: Tyler Staples
//	Date created: 7/11/2014
//	Description: 
//		Implementation of the "matrix3DIdentity" command.
//		Resets the 3D transformation matrix that all verticies are pushed through.
//		Takes 0 parameters.
//====================================================================================================

#ifndef INCLUDED_CMDMATRIX3DIDENTITY_H
#define INCLUDED_CMDMATRIX3DIDENTITY_H

#include "CmdCommand.h"

class CCmdMatrix3DIdentity : public CCmdCommand
{
public:
	CCmdMatrix3DIdentity(void) {}
	~CCmdMatrix3DIdentity(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDMATRIX3DIDENTITY_H