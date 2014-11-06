//====================================================================================================
//	File: CmdMatrix2DIdentity.h
//	Created by: Tyler Staples
//	Date created: 05/11/2014
//	Description: 
//		Implementaion of the "matrix2DIdentity" command.
//		Takes 0 parameters.
//		Loads the current matrix in MatrixManager with an identity matrix.
//====================================================================================================

#ifndef INCLUDED_CMDMATRIX2DIDENTITY_H
#define INCLUDED_CMDMATRIX2DIDENTITY_H
#pragma once

#include "CmdCommand.h"

class CCmdMatrix2DIdentity : public CCmdCommand
{
public:
	CCmdMatrix2DIdentity(void) {}
	~CCmdMatrix2DIdentity(void) {}

public:
	BOOL execute(CString &params);
};

#endif // #ifndef INCLUDED_CMDMATRIX2DIDENTITY_H