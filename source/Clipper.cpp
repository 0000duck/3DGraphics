#include "Stdafx.h"
#include "Clipper.h"
#include "Primitives.h"
#include <cassert>
#include <gl/gl.h>

// static singleton member initialization
Clipper* Clipper::spInstance = nullptr;

// --------------------------------------------------------------------

// Singleton accessor
Clipper* Clipper::Instance()
{
	if (!spInstance)
	{
		spInstance = new Clipper();
	}
	return spInstance;
}
// --------------------------------------------------------------------

Clipper::Clipper()
	:	mViewportOn(false)
	,	mClippingOn(false)
{
}
// --------------------------------------------------------------------

void Clipper::SetViewport(const CRect2& vp)
{
	if (vp.IsValid())
	{
		mViewport = vp;
	}
}
// --------------------------------------------------------------------

const CRect2& Clipper::GetViewport() const
{
	return mViewport;
}
// --------------------------------------------------------------------

void Clipper::ShowViewport()
{
	mViewportOn = true;
	DrawViewport();
}
// --------------------------------------------------------------------

void Clipper::DisableViewport()
{
	mViewportOn = false;
}
// --------------------------------------------------------------------

void Clipper::EnableClipping()
{
	mClippingOn = true;
}

void Clipper::DisableClipping()
{
	mClippingOn = false;
}

void Clipper::DrawViewport()
{
	if (mViewportOn && mViewport.IsValid())
	{
		mViewport.GetLeftSegment().DrawVertical();
		mViewport.GetBottomSegment().DrawHorizontal();
		mViewport.GetRightSegment().DrawVertical();
		mViewport.GetTopSegment().DrawHorizontal();
	}
}

eState Clipper::ClipPrimitive(CPrimitive* prim)
{
	eState rc = None;
	if (!mViewportOn || !mClippingOn)
	{
		return None;
	}

	// Get the primitive's type and call the appropriate clip method
	switch (prim->Type())
	{
	case PrimType::Point:
		rc = ClipPoint(prim);
		break;
	case PrimType::Line:
		rc = ClipLine(prim);
		break;
	case PrimType::Triangle:
		rc = ClipTriangle(prim);	// Not yet implemented
		break;
	}
	return rc;
}

eState Clipper::ClipPoint(CPrimitive* prim)
{
	CVertex2 v;
	prim->GetVert(0, v);
	unsigned int r1 = ComputeRegion(v.point);
	if (r1 == Inside)
	{
		return None;
	}
	return Culled;
}

eState Clipper::ClipLine(CPrimitive* prim)
{
	CVertex2 v1, v2;
	prim->GetVert(0, v1);
	prim->GetVert(1, v2);
	REGION r1 = ComputeRegion(v1.point);
	REGION r2 = ComputeRegion(v2.point);

	// If the result isn't 0 then we don't need to consider it
	// as both points are outside the viewport.
	if ((r1 & r2) != 0)
	{
		// "Trivially rejected"
		return Culled;
	}
	else if ((r1 | r2) == 0)
	{
		// Both points are inside the viewport; trivially accepted
		return None;
	}

	// Trim the line so it fits within the region
	CLine line(v1, v2);
	TrimLine(v1, line);
	TrimLine(v2, line);

	// Assign the fully clipped verts to the primitive
	prim->SetVert(0, v1);
	prim->SetVert(1, v2);

	return Clipped;
}

void Clipper::TrimLine(CVertex2& v, CLine& line)
{
	// Compute the region the point is in and trim until it is inside the viewport
	REGION r = ComputeRegion(v.point);
	while (r != Inside)
	{
		int x = RoundPixel(v.point.x);
		int y = RoundPixel(v.point.y);

		if ((r & Left) == Left)
		{
			if (!line.IsHorizontal())
			{
				// Only calculate the y if the line isn't horizontal
				y = line.CalcY(mViewport.MinYi());
			}
			x = mViewport.MinXi();
		}
		else if ((r & Bottom) == Bottom)
		{
			if (!line.IsVertical())
			{
				x = line.CalcX(mViewport.MaxYi());
			}
			y = mViewport.MaxYi();
		}
		else if ((r & Right) == Right)
		{
			if (!line.IsHorizontal())
			{
				y = line.CalcY(mViewport.MaxXi());
			}
			x = mViewport.MaxXi();
		}
		else if ((r & Top) == Top)
		{
			if (!line.IsVertical())
			{
				x = line.CalcX(mViewport.MinYi());
			}
			y = mViewport.MinYi();
		}

		// Update the points to the new values
		v.point.x = static_cast<float>(x);
		v.point.y = static_cast<float>(y);

		// Recompute the region
		r = ComputeRegion(v.point);
	}
}

eState Clipper::ClipTriangle(CPrimitive* prim)
{
	// TODO

	// Note: add newly created primitives to the back of the primlist
	// so they are not re-checked in CullAndClip()
	return None;
}

REGION Clipper::ComputeRegion(const CVector2& point)
{
	unsigned char region = Inside;
	CVector2 min = mViewport.mMin;
	CVector2 max = mViewport.mMax;

	if (point.x < min.x)
		region |= Left;
	else if (point.x > max.x)
		region |= Right;

	if (point.y < min.y)
		region |= Top;
	else if (point.y > max.y)
		region |= Bottom;

	return region;
}