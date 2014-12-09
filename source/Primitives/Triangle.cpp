#include "stdafx.h"
#include "Triangle.h"
#include "Line.h"
#include "Graphics/Rasterizer.h"
#include "Graphics/StateManager.h"
#include "Graphics/Viewport.h"
#include "Graphics/PrimManager.h"
#include "Containers/Matrix33.h"
#include "Containers/Vector3.h"
#include "Containers/Vertex3.h"
#include "Containers/Point.h"
#include "Utility/Transforms.h"
#include "Utility/MiniMath.h"

CTriangle::CTriangle() 
	:	CPrimitive(PrimType::Triangle)
	,	mVertIndex(0)
{
}
// ------------------------------------------------------------------------------------------

bool CTriangle::IsValid() const
{
	// Check that we have the correct number of verticies
	if (mVertIndex != MaxVerts)
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

void CTriangle::AddVertex(const CVertex3& vert)
{
	AIASSERT(mVertIndex < MaxVerts, "All verticies already defined");
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
	return MaxVerts;
}
// ------------------------------------------------------------------------------------------

CVector2 CTriangle::GetPivot() const
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
	return ((mV1.point.z + mV2.point.z + mV3.point.z) / 3.0f);
}
// ------------------------------------------------------------------------------------------

void CTriangle::Transform(const CMatrix33& tm)
{
	CVector2 pivot = GetPivot();
	CMatrix33 t = CreateTransformAroundCenter(pivot, tm);

	// Apply the transformation matrix to our verticies
	//mV1.point = Transform3HC(mV1.point, t);
	//mV2.point = Transform3HC(mV2.point, t);
	//mV3.point = Transform3HC(mV3.point, t);
}
// ------------------------------------------------------------------------------------------

CVector3 CTriangle::ComputeNormal() const
{
	CVector3 v1(mV1.point.x, mV1.point.y, mV1.point.z);
	CVector3 v2(mV2.point.x, mV2.point.y, mV2.point.z);
	CVector3 v3(mV3.point.x, mV3.point.y, mV3.point.z);

	return Cross(Normalize(v2 - v1), Normalize(v3 - v2));
}
// ------------------------------------------------------------------------------------------

void CTriangle::SetVertexNormals(const CVector3& normal)
{
	mV1.normal = normal;
	mV2.normal = normal;
	mV3.normal = normal;
}
// ------------------------------------------------------------------------------------------

void CTriangle::SetVertexColors(const CColor& color)
{
	mV1.color = color;
	mV2.color = color;
	mV3.color = color;
}
// ------------------------------------------------------------------------------------------

void CTriangle::Draw(FillMode::Mode mode)
{
	switch (mode)
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

	float divisor = CalcTimeDivisor(left.mFrom.point.y, left.mTo.point.y);
	for (int y=y1; y < y2; ++y)
	{
		float t = (y - y1) * divisor;
		float leftZ = Lerp(left.mFrom.point.z, left.mTo.point.z, t);
		float rightZ = Lerp(right.mFrom.point.z, right.mTo.point.z, t);

		CColor lc = left.GetColorAtY(y);
		CColor rc = right.GetColorAtY(y);

		// Draw the horizontal span between the two points
		if (zEnabled)
			DrawHorizontalLine_Z(leftX, rightX, y, leftZ, rightZ, lc, rc);
		else
			// No need for depth checks
			DrawHorizontalLine(leftX, rightX, y, lc, rc);

		// Increment by the inverse of the slope
		leftX += leftM;
		rightX += rightM;
	}
}
// ------------------------------------------------------------------------------------------

void CTriangle::DrawSection_Phong(const CLine& left, const CLine& right)
{
	bool zEnabled = Viewport::Instance()->ZbufferEnabled();

	// Precompute inverse slope of the lines
	const float leftM = left.CalcInvSlope();
	const float rightM = right.CalcInvSlope();
	const int y1 = RoundPixel(left.mFrom.point.y);
	const int y2 = RoundPixel(left.mTo.point.y);
	float leftX = left.mFrom.point.x;
	float rightX = right.mFrom.point.x;

	CVertex3 lp, rp;
	lp.material = left.mFrom.material;
	rp.material = right.mFrom.material;

	float divisor = CalcTimeDivisor(left.mFrom.point.y, left.mTo.point.y);
	for (int y=y1; y < y2; ++y)
	{
		float t = (y - y1) * divisor;
		lp = Vertex3Lerp(left.mFrom, left.mTo, t);
		rp = Vertex3Lerp(right.mFrom, right.mTo, t);

		if (zEnabled)
			DrawHLine_Z_Phong(lp, rp);
		else
			DrawHLine_Phong(lp, rp);

		// Increment by the inverse of the slope
		leftX += leftM;
		rightX += rightM;
	}
}
// ------------------------------------------------------------------------------------------

bool GetSidesIfFlat(CVertex3& v1, CVertex3& v2, CVertex3& v3, CLine& left, CLine& right)
{
	if (CompareFloat(v1.point.y, v2.point.y))
	{
		// Flat top
		left = (IsLeft(v1, v2)) ? CLine(v1, v3) : CLine(v2, v3);
		right = (!IsLeft(v1, v2)) ? CLine(v1, v3) : CLine(v2, v3);
		return true;
	}
	else if (CompareFloat(v2.point.y, v3.point.y))
	{
		// Flat bottom
		left = (IsLeft(v2, v3)) ? CLine(v1, v2) : CLine(v1, v3);
		right = (!IsLeft(v2, v3)) ? CLine(v1, v2) : CLine(v1, v3);
		return true;
	}
	return false;
}
// ------------------------------------------------------------------------------------------

void CTriangle::Fill()
{
	// Sort the verts from top to bottom
	CVertex3 v1(Vertex3Round(mV1));
	CVertex3 v2(Vertex3Round(mV2));
	CVertex3 v3(Vertex3Round(mV3));
	SortVertsY(v1, v2, v3);

	bool phong = (StateManager::Instance()->GetShadingMode() == ShadingMode::Phong) ? true : false;

	CLine left, right;
	if (GetSidesIfFlat(v1, v2, v3, left, right))
	{
		if (!phong)
			DrawSection(left, right);
		else
			DrawSection_Phong(left, right);
	}
	else // Split
	{
		CLine lbot, rbot; // we need 2 more lines for the bottom half
		CVertex3 v4 = GetSplitPoint(v1, v2, v3);
		GetSidesIfFlat(v1, v2, v4, left, right);	// Top half
		GetSidesIfFlat(v4, v2, v3, lbot, rbot);		// Bottom half

		// Todo: add condition for zbuffer on so no branching in drawsection
		if (!phong)
		{
			DrawSection(left, right);
			DrawSection(lbot, rbot);
		}
		else
		{
			DrawSection_Phong(left, right);
			DrawSection_Phong(lbot, rbot);
		}
	}
}
// ------------------------------------------------------------------------------------------

CVertex3 CTriangle::GetSplitPoint(const CVertex3& v1, const CVertex3& v2, const CVertex3& v3)
{
	CVertex3 v4;

	// Interpolate along V1V3 to find where v2.x intersects
	float t = (v2.point.y - v1.point.y) / (v3.point.y - v1.point.y);
	v4.point.x = Lerp(v1.point.x, v3.point.x, t);
	v4.point.z = Lerp(v1.point.z, v3.point.z, t);
	v4.point.y = v2.point.y;

	v4.worldPoint = LerpVector3(v1.worldPoint, v3.worldPoint, t);
	v4.normal = LerpVector3(v1.normal, v3.normal, t);
	v4.material = v1.material;

	// Create a temp line to find the color at that intersection
	CLine l(v1, v3);
	v4.color = l.GetColorAtY((int)v2.point.y);

	return v4;
}
// ------------------------------------------------------------------------------------------

void CTriangle::SortVertsY(CVertex3& p1, CVertex3& p2, CVertex3& p3)
{
	AIASSERT(mVertIndex == MaxVerts, "Not all verticies defined");

	if (p1.point.y > p2.point.y) std::swap(p1, p2);
	if (p1.point.y > p3.point.y) std::swap(p1, p3);
	if (p2.point.y > p3.point.y) std::swap(p2, p3);
}
// ------------------------------------------------------------------------------------------

bool IsLeft(const CVertex3& v1, const CVertex3& v2)
{
	return ((v2.point.x - v1.point.x) > 0.0f);
}