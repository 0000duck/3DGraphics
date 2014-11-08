//====================================================================================================
//	File: Viewport.h
//	Created by: Tyler Staples
//	Date created: 07/11/2014
//	Description: 
//		Keeps track of the current viewport.
//		To use this class, use the static accessor by calling Viewport::Instance().
//====================================================================================================

#ifndef INCLUDED_VIEWPORT_H
#define INCLUDED_VIEWPORT_H
#pragma once

#include "NonCopyable.h"
#include "Vector2.h"

class CRect2;

class Viewport : private NonCopyable
{
	// Constructor
	Viewport();

public:
	// Singleton accessor
	static Viewport* Instance();

	// Initializes the viewport to the rectangle described by the two points
	void Set(const CVector2& topleft, const CVector2& btmright);
	void Set(float l, float t, float r, float b);

	// Draws the outline of the viewport
	void EnableDrawing();
	void DisableDrawing();

	CRect2 GetViewport();

protected:
	void Draw();

private:
	// Static instance
	static Viewport* spInstance;

	CVector2 mOrigin;		// Top left corner of the viewport (inits at 0,0)
	float mWidth;			// Width of the viewport
	float mHeight;			// Height of the viewport
	float mAspectRatio;		// Computed aspect ratio of the viewport (width/height)

	bool mDraw;
};

#endif // #ifndef INCLUDED_CAMERA_H