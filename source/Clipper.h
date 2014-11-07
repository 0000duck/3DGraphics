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

#include "Rect2.h"


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

	// Viewport Functionality
	void SetViewport(const CRect2& vp);
	const CRect2& GetViewport() const;
	
	void ShowViewport();
	void DisableViewport();
	void EnableClipping();
	void DisableClipping();

	// Clips the primitve to the viewport.
	// Returns true if clipping occured.
	eState ClipPrimitive(CPrimitive* prim);

protected:
	// Draws the viewport on the screen
	void DrawViewport();

	eState ClipPoint(CPrimitive* prim);
	eState ClipLine(CPrimitive* prim);
	eState ClipTriangle(CPrimitive* prim);

	// Trims the line until point v is within the viewport
	void TrimLine(CVertex2& v, CLine& line);

	// Returns a byte with the first 4 bits set corresponding to
	// the region the coordinate is in.
	REGION ComputeRegion(const CVector2& point);

private:
	static Clipper* spInstance;	// Static instance

	CRect2 mViewport;
	bool mViewportOn;
	bool mClippingOn;
};

#endif