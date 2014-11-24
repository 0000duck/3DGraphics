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

// Zbuffer specific macros
#define ZBUFF32_PRECISION 8
#define ZBUFF32_DEFAULT UINT32_MAX

#define ZBUFF_PRECISION ZBUFF32_PRECISION
#define ZBUFF_DEFAULT ZBUFF32_DEFAULT

#include "Utility/NonCopyable.h"
#include "Containers/Vector2.h"
#include "Containers/Matrix44.h"
#include "Containers/Array2.h"

class CRect2;
class CPrimitive;

typedef std::vector<std::unique_ptr<CPrimitive>> PrimList;

class Viewport : private NonCopyable
{
	// Constructor
	Viewport();
	~Viewport();

public:
	// Singleton accessor
	static Viewport* Instance();

	// Destroys the current instance of this class.
	static void DestroyInstance();

	// Resets all data members to default values
	void Reset();

	// Initializes the viewport to the rectangle described by the two points
	void Set(const CVector2& topleft, const CVector2& btmright);
	void Set(float l, float t, float r, float b);

	void BackfaceCull(PrimList& primitives);

	inline bool ZbufferEnabled() const { return mZBufferOn; }
	void EnableZBuffer();
	void DisableZBuffer();
	bool CheckZDepth(const int x, const int y, const FLOAT z);
	void WipeZBuffer();

	// Draws the outline of the viewport
	inline void EnableDrawing()				{ mDraw = true; Draw(); }
	inline void DisableDrawing()			{ mDraw = false; }

	inline void EnableBackfaceCulling()		{ mBackfaceCull = true; }
	inline void DisableBackfaceCulling()	{ mBackfaceCull = false; }

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
	int mWidth;				// Width of the viewport
	int mHeight;			// Height of the viewport
	float mAspectRatio;		// Computed aspect ratio of the viewport (width/height)

	CMatrix44 mNDCToScreen; // Transformation from NDC coords to screen coords

	bool mDraw;				// Idicates if the viewport should be drawn.
	bool mBackfaceCull;
	bool mZBufferOn;
	bool mZBufferIsset;		// Has the buffer been initialized

	Array2<UINT32> mZBuffer;
};

#endif // #ifndef INCLUDED_CAMERA_H