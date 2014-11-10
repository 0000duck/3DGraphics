//====================================================================================================
//	File: Commands.h
//	Created by: Tyler Staples
//	Date created: 15/10/2014
//	Description: Common include header for all script commands.
//====================================================================================================

#ifndef INCLUDED_COMMANDS_H
#define INCLUDED_COMMANDS_H

#include "CmdDrawPixel.h"
#include "CmdColor.h"
#include "CmdFillMode.h"
#include "CmdDrawBegin.h"
#include "CmdVertex2.h"
#include "CmdVertex3.h"
#include "CmdDrawEnd.h"

#include "CmdViewport.h"
#include "CmdShowViewport.h"
#include "CmdClip.h"

#include "CmdMatrix2DIdentity.h"
#include "CmdMatrix2DTranslate.h"
#include "CmdMatrix2DScale.h"
#include "CmdMatrix2DRotate.h"
#include "CmdMatrix2DShear.h"

#include "CmdMatrix3DIdentity.h"
#include "CmdMatrix3DTranslate.h"
#include "CmdMatrix3DScale.h"
#include "CmdMatrix3DRotate.h"

#include "CmdCameraFar.h"
#include "CmdCameraFOV.h"
#include "CmdCameraNear.h"
#include "CmdCameraPersp.h"

#endif