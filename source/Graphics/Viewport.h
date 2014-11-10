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

#include "Utility/NonCopyable.h"
#include "Containers/Vector2.h"
#include "Containers/Matrix44.h"

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
	inline float GetAspectRatio() const						{ return mAspectRatio; }
	inline const CMatrix44& GetNDCToScreenMatrix() const	{ return mNDCToScreen; }

protected:
	// Draws the borders of the viewport on the screen
	void Draw();

	// Creates the NDC to screen matrix
	void CreateNDCToScreenMatrix();

private:
	// Static instance
	static Viewport* spInstance;

	CVector2 mOrigin;		// Top left corner of the viewport (inits at 0,0)
	float mWidth;			// Width of the viewport
	float mHeight;			// Height of the viewport
	float mAspectRatio;		// Computed aspect ratio of the viewport (width/height)

	CMatrix44 mNDCToScreen; // Transformation from NDC coords to screen coords

	bool mDraw;				// Idicates if the viewport should be drawn.
};

#endif // #ifndef INCLUDED_CAMERA_H