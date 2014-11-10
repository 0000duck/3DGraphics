//====================================================================================================
//	File: Clipper.h
//	Created by: Tyler Staples
//	Date created: 26/10/2014
//	Description: 
//		- Keeps track of the current viewport
//		- Clips anything outside the viewport
//		To use this class, use the static accessor by calling Clipper::Instance().
//====================================================================================================

#ifndef INCLUDED_CLIPPER_H
#define INCLUDED_CLIPPER_H
#pragma once

#include "Containers/Rect2.h"


typedef unsigned int REGION;
enum eRegion
{
	Inside	= 0,	// 0000
	Left	= 1,	// 0001
	Right	= 2,	// 0010
	Bottom	= 4,	// 0100
	Top		= 8,	// 1000
};

enum eState
{
	None,
	Clipped,
	Culled
};


class Clipper
{
	// Constructors
	Clipper();
	Clipper(const Clipper&);
	Clipper& operator=(const Clipper&);

public:
	// Singleton accessor
	static Clipper* Instance();
	
	void EnableClipping();
	void DisableClipping();

	// Clips the primitve to the viewport.
	// Returns true if clipping occured.
	eState ClipPrimitive(CPrimitive* prim);

protected:

	eState ClipPoint(CPrimitive* prim, const CRect2& vp);
	eState ClipLine(CPrimitive* prim, const CRect2& vp);
	eState ClipTriangle(CPrimitive* prim, const CRect2& vp);

	// Trims the line until point v is within the viewport
	void TrimLine(CVertex2& v, CLine& line, const CRect2& vp);

	// Returns a byte with the first 4 bits set corresponding to
	// the region the coordinate is in.
	REGION ComputeRegion(const CVector2& point, const CRect2& vp);

private:
	// Static instance
	static Clipper* spInstance;

	bool mClippingOn;	// If clipping is enabled
};

#endif