#include "Stdafx.h"
#include "Viewport.h"
#include "Containers/Rect2.h"
#include "Containers/Vector4.h"
#include "Camera.h"

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

	CreateNDCToScreenMatrix();
}
// ------------------------------------------------------------------------------------------

void Viewport::Set(float l, float t, float r, float b)
{
	mOrigin = CVector2(l, t);
	mWidth = r;
	mHeight = b;
	mAspectRatio = mWidth / mHeight;

	CreateNDCToScreenMatrix();
}
// ------------------------------------------------------------------------------------------

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
// ------------------------------------------------------------------------------------------

void Viewport::CreateNDCToScreenMatrix()
{
	float n = Camera::Instance()->GetNear();
	float f = Camera::Instance()->GetFar();
	float d = 1.0f; // temp depth until i figure out where to obtain the value

	float width = mWidth * 0.5f;
	float height = mHeight * 0.5f;

	mNDCToScreen.Identity();
	CVector4 c0, c1, c2, c3;
	mNDCToScreen.GetColumns(c0, c1, c2, c3);

	c0.x = width;
	c1.y = -height;
	c2.z = d / 2;
	c3.x = width + mOrigin.x;
	c3.y = height + mOrigin.y;
	c3.z = d / 2;

	mNDCToScreen.SetColumns(c0, c1, c2, c3);
}