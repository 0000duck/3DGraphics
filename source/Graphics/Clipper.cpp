#include "Stdafx.h"
#include "Clipper.h"
#include "Viewport.h"
#include "Primitives/Line.h"
#include <cassert>

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

void Clipper::DestroyInstance()
{
	if (spInstance)
	{
		delete spInstance;
		spInstance = nullptr;
	}
}
// --------------------------------------------------------------------

Clipper::Clipper()
	:	mClippingOn(false)
{
}

// --------------------------------------------------------------------

void Clipper::Reset()
{
	mClippingOn = false;
}
// --------------------------------------------------------------------

void Clipper::EnableClipping()
{
	mClippingOn = true;
}
// ------------------------------------------------------------------------------------------

void Clipper::DisableClipping()
{
	mClippingOn = false;
}
// ------------------------------------------------------------------------------------------

eState Clipper::ClipPrimitive(CPrimitive* prim)
{
	eState rc = None;
	if (!mClippingOn)
	{
		return None;
	}

	// Get the viewport
	const CRect2 vp = Viewport::Instance()->GetViewport();

	// Get the primitive's type and call the appropriate clip method
	switch (prim->Type())
	{
	case PrimType::Point:
		// todo: fix this
		//rc = ClipPoint(prim, vp);
		break;
	case PrimType::Line:
		rc = ClipLine(*static_cast<CLine*>(prim), vp);
		break;
	case PrimType::Triangle:
		rc = ClipTriangle(prim, vp);	// Not yet implemented
		break;
	}
	return rc;
}
// ------------------------------------------------------------------------------------------

eState Clipper::ClipPoint(CVertex2& v, const CRect2& vp)
{
	unsigned int r1 = ComputeRegion(v.point, vp);
	if (r1 == Inside)
	{
		return None;
	}
	return Culled;
}
// ------------------------------------------------------------------------------------------

eState Clipper::ClipLine(CLine& line, const CRect2& vp)
{
	// Computer the regions of the 2 points
	CVertex3 v1(line.mFrom);
	CVertex3 v2(line.mTo);
	REGION r1 = ComputeRegion(v1.Get2DPoint(), vp);
	REGION r2 = ComputeRegion(v2.Get2DPoint(), vp);

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
	TrimLine(v1, line, vp);
	TrimLine(v2, line, vp);

	// Assign the fully clipped verts to the primitive
	line.mFrom = v1;
	line.mTo = v2;

	return Clipped;
}
// ------------------------------------------------------------------------------------------

void Clipper::TrimLine(CVertex3& v, const CLine& line, const CRect2& vp)
{
	// Compute the region the point is in and trim until it is inside the viewport
	REGION r = ComputeRegion(v.Get2DPoint(), vp);
	while (r != Inside)
	{
		int x = RoundPixel(v.point.x);
		int y = RoundPixel(v.point.y);

		if ((r & Left) == Left)
		{
			if (!line.IsHorizontal())
			{
				// Only calculate the y if the line isn't horizontal
				y = line.CalcY(vp.MinYi());
			}
			x = vp.MinXi();
		}
		else if ((r & Bottom) == Bottom)
		{
			if (!line.IsVertical())
			{
				x = line.CalcX(vp.MaxYi());
			}
			y = vp.MaxYi();
		}
		else if ((r & Right) == Right)
		{
			if (!line.IsHorizontal())
			{
				y = line.CalcY(vp.MaxXi());
			}
			x = vp.MaxXi();
		}
		else if ((r & Top) == Top)
		{
			if (!line.IsVertical())
			{
				x = line.CalcX(vp.MinYi());
			}
			y = vp.MinYi();
		}

		// Update the points to the new values
		v.point.x = static_cast<float>(x);
		v.point.y = static_cast<float>(y);

		// Recompute the region
		r = ComputeRegion(v.Get2DPoint(), vp);
	}
}
// ------------------------------------------------------------------------------------------

eState Clipper::ClipTriangle(CPrimitive* prim, const CRect2& vp)
{
	// TODO

	// Note: add newly created primitives to the back of the primlist
	// so they are not re-checked in CullAndClip()
	return None;
}
// ------------------------------------------------------------------------------------------

REGION Clipper::ComputeRegion(const CVector2& point, const CRect2& vp)
{
	unsigned char region = Inside;
	CVector2 min = vp.mMin;
	CVector2 max = vp.mMax;

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