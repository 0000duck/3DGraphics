#include "Stdafx.h"
#include "Viewport.h"
#include "Rect2.h"

// static singleton member initialization
Viewport* Viewport::spInstance = nullptr;

// ------------------------------------------------------------------------------------------

// Singleton accessor
Viewport* Viewport::Instance()
{
	if (!spInstance)
	{
		spInstance = new Viewport();
	}
	return spInstance;
}
// ------------------------------------------------------------------------------------------

// Default constructor
Viewport::Viewport()
	:	mOrigin(0.0f, 0.0f)
	,	mWidth(0.0f)
	,	mHeight(0.0f)
	,	mAspectRatio(0.0f)
	,	mDraw(false)
{
}
// ------------------------------------------------------------------------------------------

void Viewport::Set(const CVector2& topleft, const CVector2& btmright)
{
	mOrigin = topleft;
	mWidth = btmright.x;
	mHeight = btmright.y;
	mAspectRatio = mWidth / mHeight;
}
// ------------------------------------------------------------------------------------------

void Viewport::Set(float l, float t, float r, float b)
{
	mOrigin = CVector2(l, t);
	mWidth = r;
	mHeight = b;
	mAspectRatio = mWidth / mHeight;
}

void Viewport::EnableDrawing()
{
	mDraw = true;
	Draw();
}
// ------------------------------------------------------------------------------------------

void Viewport::DisableDrawing()
{
	mDraw = false;
}
// ------------------------------------------------------------------------------------------

void Viewport::Draw()
{
	CRect2 r(mOrigin.x, mOrigin.y, mWidth, mHeight);
	if (r.IsValid())
	{
		r.GetLeftSegment().DrawVertical();
		r.GetBottomSegment().DrawHorizontal();
		r.GetRightSegment().DrawVertical();
		r.GetTopSegment().DrawHorizontal();
	}
}
// ------------------------------------------------------------------------------------------

CRect2 Viewport::GetViewport()
{
	return CRect2(mOrigin.x, mOrigin.y, mWidth, mHeight);
}