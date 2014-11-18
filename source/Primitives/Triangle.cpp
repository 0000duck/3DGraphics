#include "stdafx.h"
#include "Triangle.h"
#include "Graphics/Rasterizer.h"
#include "Graphics/StateManager.h"
#include "Primitives.h"
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

void CTriangle::GetVert(int index, CVertex2& out)
{
	AIASSERT(index >= 0 && index < kVerts, "Index out of range");
	if (index == 0)
		out = mV1;
	if (index == 1)
		out = mV2;
	if (index == 2)
		out = mV3;
}
// ------------------------------------------------------------------------------------------

void CTriangle::SetVert(int index, const CVertex2& v)
{
	AIASSERT(index >= 0 && index < kVerts, "Index out of range");
	if (index == 0)
		mV1 = v;
	if (index == 1)
		mV2 = v;
	if (index == 2)
		mV3 = v;
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
	// Cache the points
	CLine l1(mV1, mV2);
	CLine l2(mV2, mV3);
	CLine l3(mV1, mV3);

	l1.Draw();
	l2.Draw();
	l3.Draw();
}
// ------------------------------------------------------------------------------------------

void CTriangle::DrawPoints()
{
	DrawVertex(mV1);
	DrawVertex(mV2);
	DrawVertex(mV3);
}
// ------------------------------------------------------------------------------------------

void DrawSection(const CLine& left, const CLine& right)
{
	float leftM = left.CalcInvSlope();
	float rightM = right.CalcInvSlope();
	int y1 = static_cast<int>(left.mV1.point.y);
	int y2 = static_cast<int>(left.mV2.point.y);
	float leftX = left.mV1.point.x;
	float rightX = right.mV1.point.x;

	for (int y=y1; y < y2; ++y)
	{
		// Create verts from the left and right points
		CVertex2 v1(ceilf(leftX), y, left.GetColorAtY(y));
		CVertex2 v2(ceilf(rightX), y, right.GetColorAtY(y)); 

		// Draw a line between them
		DrawLine(v1, v2);

		leftX += leftM;
		rightX += rightM;
	}
}
// ------------------------------------------------------------------------------------------

void CTriangle::Fill()
{
	// Sort the verts from top to bottom
	CVertex2 v1(mV1), v2(mV2), v3(mV3);
	v1.Ceil(); v2.Ceil(); v3.Ceil();
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
	v4.point.x = v1.point.x + t * (v3.point.x - v1.point.x);
	v4.point.y = v2.point.y;

	// Create a temp line to find the color at that intersection
	CLine l(v1, v3);
	v4.color = l.GetColorAtY(v2.point.y);

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