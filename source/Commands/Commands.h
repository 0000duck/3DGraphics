//====================================================================================================
//	File: Commands.h
//	Created by: Tyler Staples
//	Date created: 15/10/2014
//	Description: Common include header for all script commands.
//====================================================================================================

#ifndef INCLUDED_COMMANDS_H
#define INCLUDED_COMMANDS_H

// Drawing
#include "CmdDrawPixel.h"
#include "CmdColor.h"
#include "CmdFillMode.h"
#include "CmdDrawBegin.h"
#include "CmdVertex2.h"
#include "CmdVertex3.h"
#include "CmdDrawEnd.h"

// Viewport
#include "CmdViewport.h"
#include "CmdShowViewport.h"
#include "CmdClip.h"
#include "CmdBackfaceCull.h"
#include "CmdZBuffer.h"

// 2D matricies
#include "CmdMatrix2DIdentity.h"
#include "CmdMatrix2DTranslate.h"
#include "CmdMatrix2DScale.h"
#include "CmdMatrix2DRotate.h"
#include "CmdMatrix2DShear.h"

// 3D matrices
#include "CmdMatrix3DIdentity.h"
#include "CmdMatrix3DTranslate.h"
#include "CmdMatrix3DScale.h"
#include "CmdMatrix3DRotate.h"

// Camera
#include "CmdCameraFar.h"
#include "CmdCameraFOV.h"
#include "CmdCameraNear.h"
#include "CmdCameraPersp.h"

// Lighting
#include "CmdAttenConstant.h"
#include "CmdAttenLinear.h"
#include "CmdAttenQuadratic.h"
#include "CmdWorldAmbient.h"
#include "CmdLightAmbient.h"
#include "CmdLightDiffuse.h"
#include "CmdLightSpecular.h"
#include "CmdDirectionalLight.h"
#include "CmdPointLight.h"
#include "CmdSpotLight.h"
#include "CmdClearLights.h"

// Shading
#include "CmdNormal.h"
#include "CmdMaterialAmbient.h"
#include "CmdMaterialDiffuse.h"
#include "CmdMaterialEmissive.h"
#include "CmdMaterialShininess.h"
#include "CmdMaterialSpecular.h"

#include "CmdShadingMode.h"

#endif