//====================================================================================================
//	File: CmdSpotLight.h
//	Created by: Tyler Staples
//	Date created: 29/11/2014
//	Description: 
//		Implementaion of the "spotLight" command.
//		Takes 8 params (float) for the (x, y, z) position of the light,
//		(x,y,z) normalized direction the light points in,
//		the angle the cone makes in degrees, and the decay factor.
//====================================================================================================

#ifndef INCLUDED_CMDSPOTLIGHT_H
#define INCLUDED_CMDSPOTLIGHT_H

#include "CmdCommand.h"

class CCmdSpotLight : public CCmdCommand
{
public:
	CCmdSpotLight(void) {}
	~CCmdSpotLight(void) {}

public:
	BOOL execute(CString &params);

};

#endif //#ifndef INCLUDED_CMDSPOTLIGHT_H