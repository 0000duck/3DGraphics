//====================================================================================================
//	File: CmdMatrix3DTranslate.h
//	Created by: Tyler Staples
//	Date created: 7/11/2014
//	Description: 
//		Implementation of the "matrix3DTranslate" command.
//		Combines a translation matrix with the current transformation matrix.
//		Takes 3 parameters for the amount to translate by in each axis.
//====================================================================================================

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