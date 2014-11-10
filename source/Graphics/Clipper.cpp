#include "Stdafx.h"
#include "Clipper.h"
#include "Primitives/Primitives.h"
#include "Viewport.h"
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

Clipper::Clipper()
	:	mClippingOn(false)
{
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
		rc = ClipPoint(prim, vp);
		break;
	case PrimType::Line:
		rc = ClipLine(prim, vp);
		break;
	case PrimType::Triangle:
		rc = ClipTriangle(prim, vp);	// Not yet implemented
		break;
	}
	return rc;
}
// ------------------------------------------------------------------------------------------

eState Clipper::ClipPoint(CPrimitive* prim, const CRect2& vp)
{
	CVertex2 v;
	prim->GetVert(0, v);
	unsigned int r1 = ComputeRegion(v.point, vp);
	if (r1 == Inside)
	{
		return None;
	}
	return Culled;
}
// ------------------------------------------------------------------------------------------

eState Clipper::ClipLine(CPrimitive* prim, const CRect2& vp)
{
	// Computer the regions of the 2 points
	CVertex2 v1, v2;
	prim->GetVert(0, v1);
	prim->GetVert(1, v2);
	REGION r1 = ComputeRegion(v1.point, vp);
	REGION r2 = ComputeRegion(v2.point, vp);

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
	TrimLine(v1, line, vp);
	TrimLine(v2, line, vp);

	// Assign the fully clipped verts to the primitive
	prim->SetVert(0, v1);
	prim->SetVert(1, v2);

	return Clipped;
}
// ------------------------------------------------------------------------------------------

void Clipper::TrimLine(CVertex2& v, CLine& line, const CRect2& vp)
{
	// Compute the region the point is in and trim until it is inside the viewport
	REGION r = ComputeRegion(v.point, vp);
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
		r = ComputeRegion(v.point, vp);
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