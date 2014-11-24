#include "stdafx.h"
#include "Triangle.h"
#include "Line.h"
#include "Graphics/Rasterizer.h"
#include "Graphics/StateManager.h"
#include "Graphics/Viewport.h"
#include "Containers/Matrix33.h"
#include "Containers/Vector3.h"
#include "Containers/Point.h"
#include "Utility/Transforms.h"
#include "Utility/MiniMath.h"

CTriangle::CTriangle() 
	:	CPrimitive(PrimType::Triangle)
	,	mVertIndex(0)
{
}
// ------------------------------------------------------------------------------------------

CTriangle::CTriangle(const CTriangle& rhs)
	:	CPrimitive(rhs.mType)
{
	*this = rhs;
}
// ------------------------------------------------------------------------------------------

CTriangle& CTriangle::operator=(const CTriangle& rhs)
{
	if (this != &rhs)
	{
		// Copy verticies over
		mV1 = rhs.mV1;
		mV2 = rhs.mV2;
		mV3 = rhs.mV3;
	}
	return *this;
}
// ------------------------------------------------------------------------------------------

bool CTriangle::IsValid() const
{
	// Check that we have the correct number of verticies
	if (mVertIndex != kVerts)
	{
		return false;
	}
	else
	{
		// Ensure no more than 2 verticies are parallel
		if (CompareFloat(mV1.point.x, mV2.point.x) &&
			CompareFloat(mV1.point.x, mV3.point.x) ||
			CompareFloat(mV1.point.y, mV2.point.y) &&
			CompareFloat(mV1.point.y, mV3.point.y))
		{
			return false;
		}
	}
	return (CPrimitive::IsValid());
}
// ------------------------------------------------------------------------------------------

void CTriangle::AddVertex(const CVertex2& vert)
{
	AIASSERT(mVertIndex < kVerts, "All verticies already defined");
	switch (mVertIndex++)
	{
	case 0:
	mV1 = vert;
		break;
	case 1:
		mV2 = vert;
		break;
	case 2:
		mV3 = vert;
		break;
	}
}
// ------------------------------------------------------------------------------------------

const int CTriangle::VertexCount() const
{
	return mVertIndex;
}
// ------------------------------------------------------------------------------------------

const int CTriangle::MaxVerticies() const
{
	return kVerts;
}
// ------------------------------------------------------------------------------------------

CVector2 CTriangle::GetPivot()
{
	// todo: call get center from bounding box class
	CVector2 pmax(max(max(mV1.point.x, mV2.point.x), mV3.point.x),
				  max(max(mV1.point.y, mV2.point.y), mV3.point.y));
	CVector2 pmin(min(min(mV1.point.x, mV2.point.x), mV3.point.x),
				  min(min(mV1.point.y, mV2.point.y), mV3.point.y));

	float midx = (abs(pmax.x) - abs(pmin.x)) * 0.5f;
	float midy = (abs(pmax.y) - abs(pmin.y)) * 0.5f;

	return CVector2(pmin.x + midx, pmin.y + midy);
}
// ------------------------------------------------------------------------------------------

float CTriangle::GetZDepth()
{
	return ((mV1.z + mV2.z + mV3.z) / 3.0f);
}
// ------------------------------------------------------------------------------------------

void CTriangle::Transform(const CMatrix33& tm)
{
	CVector2 pivot = GetPivot();
	CMatrix33 t = CreateTransformAroundCenter(pivot, tm);

	// Apply the transformation matrix to our verticies
	mV1.point = Transform3HC(mV1.point, t);
	mV2.point = Transform3HC(mV2.point, t);
	mV3.point = Transform3HC(mV3.point, t);
}
// ------------------------------------------------------------------------------------------

CVector3 CTriangle::ComputeNormal()
{
	CVector3 v1(mV1.point.x, mV1.point.y, mV1.z);
	CVector3 v2(mV2.point.x, mV2.point.y, mV2.z);
	CVector3 v3(mV3.point.x, mV3.point.y, mV3.z);

	return Cross(Normalize(v2 - v1), Normalize(v3 - v2));
}
// ------------------------------------------------------------------------------------------

void CTriangle::Draw()
{
	FillMode::Mode fMode = StateManager::Instance()->GetFillMode();
	switch (fMode)
	{
	case FillMode::Point:
		DrawPoints();
		break;
	case FillMode::Line:
		DrawSolid();
		break;
	case FillMode::Fill:
		Fill();
		break;
	}
}
// ------------------------------------------------------------------------------------------

void CTriangle::DrawSolid()
{
	DrawLine(mV1, mV2);
	DrawLine(mV2, mV3);
	DrawLine(mV1, mV3);
}
// ------------------------------------------------------------------------------------------

void CTriangle::DrawPoints()
{
	DrawVertex(mV1);
	DrawVertex(mV2);
	DrawVertex(mV3);
}
// ------------------------------------------------------------------------------------------

void CTriangle::DrawSection(const CLine& left, const CLine& right)
{
	bool zEnabled = Viewport::Instance()->ZbufferEnabled();

	// Precompute inverse slope of the lines
	const float leftM = left.CalcInvSlope();
	const float rightM = right.CalcInvSlope();

	const int y1 = RoundPixel(left.mFrom.point.y);
	const int y2 = RoundPixel(left.mTo.point.y);

	float leftX = left.mFrom.point.x;
	float rightX = right.mFrom.point.x;

	float divisor = CalcTimeDivisor(y1, y2);
	for (int y=y1; y < y2; ++y)
	{
		float t = (y - y1) * divisor;
		float leftZ = Lerp(left.mFrom.z, left.mTo.z, t);
		float rightZ = Lerp(right.mFrom.z, right.mTo.z, t);

		// Draw the horizontal span between the two points
		if (zEnabled)
		{
			DrawHorizontalLine_Z(leftX, rightX, y, leftZ, rightZ, left.GetColorAtY(y), right.GetColorAtY(y));
		}
		else
		{
			// No need for depth checks
			DrawHorizontalLine(leftX, rightX, y, left.GetColorAtY(y), right.GetColorAtY(y));
		}

		// Increment by the inverse of the slope
		leftX += leftM;
		rightX += rightM;
	}
}
// ------------------------------------------------------------------------------------------

void CTriangle::Fill()
{
	// Sort the verts from top to bottom
	CVertex2 v1(mV1), v2(mV2), v3(mV3);
	v1.Ceil(); v2.Ceil(); v3.Ceil();	// Prevent edge fighting
	SortVertsY(v1, v2, v3);

	if (CompareFloat(v1.point.y, v2.point.y))
	{
		// Flat top
		CLine left = (IsLeft(v1, v2)) ? CLine(v1, v3) : CLine(v2, v3);
		CLine right = (!IsLeft(v1, v2)) ? CLine(v1, v3) : CLine(v2, v3);
		DrawSection(left, right);
	}
	else if (CompareFloat(v2.point.y, v3.point.y))
	{
		// Flat bottom
		CLine left = (IsLeft(v2, v3)) ? CLine(v1, v2) : CLine(v1, v3);
		CLine right = (!IsLeft(v2, v3)) ? CLine(v1, v2) : CLine(v1, v3);
		DrawSection(left, right);
	}
	else
	{
		// Split
		CVertex2 v4 = GetSplitPoint(v1, v2, v3);

		if (IsLeft(v2, v4))
		{
			// v2 is on the left
			DrawSection(CLine(v1, v2), CLine(v1, v4));	// Top half
			DrawSection(CLine(v2, v3), CLine(v4, v3));	// Bottom half
		}
		else
		{
			// v2 is on the right
			DrawSection(CLine(v1, v4), CLine(v1, v2));
			DrawSection(CLine(v4, v3), CLine(v2, v3));
		}
	}
}
// ------------------------------------------------------------------------------------------

CVertex2 CTriangle::GetSplitPoint(const CVertex2& v1, const CVertex2& v2, const CVertex2& v3)
{
	CVertex2 v4;

	// Interpolate along V1V3 to find where v2.x intersects
	float t = (v2.point.y - v1.point.y) / (v3.point.y - v1.point.y);
	v4.point.x = Lerp(v1.point.x, v3.point.x, t);
	v4.z = Lerp(v1.z, v3.z, t);
	v4.point.y = v2.point.y;

	// Create a temp line to find the color at that intersection
	CLine l(v1, v3);
	v4.color = l.GetColorAtY((int)v2.point.y);

	return v4;
}
// ------------------------------------------------------------------------------------------

void CTriangle::SortVertsY(CVertex2& p1, CVertex2& p2, CVertex2& p3)
{
	AIASSERT(mVertIndex == kVerts, "Not all verticies defined");

	if (p1.point.y > p2.point.y) std::swap(p1, p2);
	if (p1.point.y > p3.point.y) std::swap(p1, p3);
	if (p2.point.y > p3.point.y) std::swap(p2, p3);
}
// ------------------------------------------------------------------------------------------

bool IsLeft(const CVertex2& v1, const CVertex2& v2)
{
	return ((v2.point.x - v1.point.x) > 0.0f);
}