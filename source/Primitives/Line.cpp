#include "stdafx.h"
#include "Line.h"
#include "Graphics/StateManager.h"
#include "Graphics/Rasterizer.h"
#include "Containers/Vector3.h"
#include "Containers/Matrix33.h"
#include "Utility/Transforms.h"


CLine::CLine() 
	:	CPrimitive(PrimType::Line)
	,	mVertCount(0)
	,	mSlope(0.0f)
{}
// ------------------------------------------------------------------------------------------

CLine::CLine(float x1, float y1, float x2, float y2, const CColor& c1, const CColor& c2)
	:	CPrimitive(PrimType::Line)
	,	mVertCount(0)
	,	mFrom(x1, y1, c1)
	,	mTo(x2, y2, c2)
{
	mSlope = CalcSlope();
}
// ------------------------------------------------------------------------------------------

CLine::CLine(const CVector2& p1, const CVector2& p2, const CColor& c1, const CColor& c2)
	:	CPrimitive(PrimType::Line)
	,	mVertCount(0)
	,	mFrom(p1, c1)
	,	mTo(p2, c2)
{
	mSlope = CalcSlope();
}
// ------------------------------------------------------------------------------------------

CLine::CLine(const CVertex2& p1, const CVertex2& p2)
	:	CPrimitive(PrimType::Line)
	,	mVertCount(2)
	,	mFrom(p1)
	,	mTo(p2)
{
	mSlope = CalcSlope();
}
// ------------------------------------------------------------------------------------------

CLine::CLine(const CLine& rhs)
	:	CPrimitive(rhs.mType)
{
	*this = rhs;
}
// ------------------------------------------------------------------------------------------

CLine& CLine::operator=(const CLine& rhs)
{
	if (this != &rhs)
	{
		mVertCount = rhs.mVertCount;
		mFrom = rhs.mFrom;
		mTo = rhs.mTo;
	}
	return *this;
}
// ------------------------------------------------------------------------------------------

bool CLine::IsValid() const
{
	// Check that we have the correct number of verticies
	if (mVertCount != MaxVerts)
	{
		return false;
	}
	return (CPrimitive::IsValid());
}
// ------------------------------------------------------------------------------------------

void CLine::AddVertex(const CVertex2& vert)
{
	if (mVertCount == 0)
	{
		mFrom = vert;
		mVertCount++;
	}
	else if (mVertCount > 0 && mVertCount < MaxVerts)
	{
		mTo = vert;
		mVertCount++;

		// Get the slope now that we have both points
		mSlope = CalcSlope();
	}
}
// ------------------------------------------------------------------------------------------

const int CLine::VertexCount() const
{
	return mVertCount;
}
// ------------------------------------------------------------------------------------------

const int CLine::MaxVerticies() const
{
	return MaxVerts;
}
// ------------------------------------------------------------------------------------------

CVector2 CLine::GetPivot()
{
	// todo: call get center from bounding box class
	CVector2 pmax(max(mFrom.point.x, mTo.point.x), max(mFrom.point.y, mTo.point.y));
	CVector2 pmin(min(mFrom.point.x, mTo.point.x), min(mFrom.point.y, mTo.point.y));

	float midx = (abs(pmax.x) - abs(pmin.x)) * 0.5f;
	float midy = (abs(pmax.y) - abs(pmin.y)) * 0.5f;

	return CVector2(pmin.x + midx, pmin.y + midy);
}
// ------------------------------------------------------------------------------------------

float CLine::GetZDepth()
{
	return ((mFrom.z + mTo.z) * 0.5f);
}
// ------------------------------------------------------------------------------------------

void CLine::Transform(const CMatrix33& tm)
{
	CMatrix33 a = CreateTransformAroundCenter(GetPivot(), tm);

	// Apply transformation matrix to verts
	mFrom.point = Transform3HC(mFrom.point, tm);
	mTo.point = Transform3HC(mTo.point, tm);
}
// ------------------------------------------------------------------------------------------

void CLine::SetVerts(const CVertex2& v1, const CVertex2& v2)
{
	mFrom = v1;
	mTo = v2;
}
// ------------------------------------------------------------------------------------------

void CLine::Draw(FillMode::Mode mode)
{
	if (mode == FillMode::Point)
	{
		DrawPoints();
	}
	else if (mode == FillMode::Line || mode == FillMode::Fill)
	{
		DrawLine(mFrom, mTo);
	}
}
// ------------------------------------------------------------------------------------------

void CLine::DrawSolid()
{
	DrawLine(mFrom, mTo);
}
// ------------------------------------------------------------------------------------------

void CLine::DrawHorizontal()
{
	DrawHorizontalLine(mFrom.point.x, mTo.point.x, mFrom.point.y, mFrom.color, mTo.color);
}
// ------------------------------------------------------------------------------------------

void CLine::DrawVertical()
{
	DrawVerticalLine(mFrom.point.y, mTo.point.y, mFrom.point.x, mFrom.color, mTo.color);
}
// ------------------------------------------------------------------------------------------

void CLine::DrawPoints()
{
	DrawVertex(mFrom);
	DrawVertex(mTo);
}
// ------------------------------------------------------------------------------------------

float CLine::CalcSlope() const
{
	return ::CalcSlope(mFrom.point, mTo.point);
}
// ------------------------------------------------------------------------------------------

float CLine::CalcInvSlope() const
{
	return ::CalcInvSlope(mFrom.point, mTo.point);
}
// ------------------------------------------------------------------------------------------

int CLine::CalcY(int x) const
{
	float m = CalcSlope();
	float b = mFrom.point.y - (m * mFrom.point.x);
	return RoundPixel(m * x + b);
}
// ------------------------------------------------------------------------------------------

int CLine::CalcX(int y) const
{
	float m = CalcSlope();
	float b = mFrom.point.y - (m * mFrom.point.x);
	return RoundPixel((y - b) / m);
}
// ------------------------------------------------------------------------------------------

CColor CLine::GetColorAtY(int y) const
{
	// Calling CalcTimeDivisor saves us from handling divide by 0
	float divisor = CalcTimeDivisor(mFrom.point.y, mTo.point.y);
	float t = (y - mFrom.point.y) * divisor;
	return LerpColor(mFrom.color, mTo.color, t);
}
// ------------------------------------------------------------------------------------------

bool CLine::IsVertical() const
{
	return (RoundPixel(mFrom.point.x) == RoundPixel(mTo.point.x));
}
// ------------------------------------------------------------------------------------------

bool CLine::IsHorizontal() const
{
	return (RoundPixel(mFrom.point.y) == RoundPixel(mTo.point.y));
}

//====================================================================================================
// Helper definitions
//====================================================================================================

bool IsVertical(const CVector2& from, const CVector2& to)
{
	return (RoundPixel(from.x) == RoundPixel(to.x));
}
// ------------------------------------------------------------------------------------------

bool IsHorizontal(const CVector2& from, const CVector2& to)
{
	return (RoundPixel(from.y) == RoundPixel(to.y));
}

float GetYIntercept(const CVector2& from, const float slope)
{
	return (from.y - (slope * from.x));
}
// ------------------------------------------------------------------------------------------

float GetYIntercept(const int fromX, const int fromY, const float slope)
{
	return (fromY - (slope * fromX));
}
// ------------------------------------------------------------------------------------------

float CalcSlope(const CVector2& from, const CVector2& to)
{
	float m = 0.0f;
	float dy = to.y - from.y;		// rise
	float dx = to.x - from.x;		// run
	if (dx > 0.0f || dx < 0.0f)
	{
		m = dy / dx;
	}
	return m;
}
// ------------------------------------------------------------------------------------------

float CalcInvSlope(const CVector2& from, const CVector2& to)
{
	float m = 0.0f;
	float dy = to.y - from.y;	// rise
	float dx = to.x - from.x;	// run
	if (dx > 0.0f || dx < 0.0f)
	{
		m = dx / dy; // run over rise
	}
	return m;
}
// ------------------------------------------------------------------------------------------

void DrawHorizontalLine(const CVertex2& from, const CVertex2& to)
{
	DrawHorizontalLine(from.point.x, to.point.x, from.point.y, from.color, to.color);
}
// ------------------------------------------------------------------------------------------

void DrawHorizontalLine(float fromX, float toX, float y, const CColor& cfrom, const CColor& cto)
{
	const int _axis = RoundPixel(y);
	const int _from = RoundPixel(fromX);
	const int _to = RoundPixel(toX);

	float divisor = CalcTimeDivisor(fromX, toX);
	int inc = (divisor < 0.0f) ? -1 : 1;

	for (int x = _from; x != _to; x += inc)
	{
		float t = (x - _from) * divisor;
		CColor pixelColor = LerpColor(cfrom, cto, t);
		DrawVertex(x, _axis, pixelColor);
	}
}
// ------------------------------------------------------------------------------------------

void DrawVerticalLine(const CVertex2& from, const CVertex2& to)
{
	DrawVerticalLine(from.point.y, to.point.y, from.point.x, from.color, to.color);
}
// ------------------------------------------------------------------------------------------

void DrawVerticalLine(float fromY, float toY, float x, const CColor& cfrom, const CColor& cto)
{
	const int _axis = RoundPixel(x);
	const int _from = RoundPixel(fromY);
	const int _to = RoundPixel(toY);

	float divisor = CalcTimeDivisor(fromY, toY);
	int inc = (divisor < 0.0f) ? -1 : 1;

	for (int y = _from; y != _to; y += inc)
	{
		float t = (y - _from) * divisor;
		CColor pixelColor = LerpColor(cfrom, cto, t);
		DrawVertex(_axis, y, pixelColor);
	}
}
// ------------------------------------------------------------------------------------------

void DrawHorizontalLine_Z(const CVertex2& from, const CVertex2& to)
{
	DrawHorizontalLine_Z(from.point.x, to.point.x, from.point.y, from.z, to.z, from.color, to.color);
}
// ------------------------------------------------------------------------------------------

void DrawHorizontalLine_Z(float fromX, float toX, float y, float z1, float z2, const CColor& cfrom, const CColor& cto)
{
	const int _axis = RoundPixel(y);
	const int _from = RoundPixel(fromX);
	const int _to = RoundPixel(toX);

	float divisor = CalcTimeDivisor(fromX, toX);
	int inc = (divisor < 0.0f) ? -1 : 1;

	for (int x = _from; x != _to; x += inc)
	{
		float t = (x - _from) * divisor;
		CColor pixelColor = LerpColor(cfrom, cto, t);

		float z = Lerp(z1, z2, t);
		DrawVertex_Z(x, _axis, z, pixelColor);
	}
}
// ------------------------------------------------------------------------------------------

void DrawVerticalLine_Z(const CVertex2& from, const CVertex2& to)
{
	DrawVerticalLine_Z(from.point.x, to.point.x, from.point.y, from.z, to.z, from.color, to.color);
}
// ------------------------------------------------------------------------------------------

void DrawVerticalLine_Z(float fromY, float toY, float x, float z1, float z2, const CColor& cfrom, const CColor& cto)
{
	const int _axis = RoundPixel(x);
	const int _from = RoundPixel(fromY);
	const int _to = RoundPixel(toY);

	float divisor = CalcTimeDivisor(fromY, toY);
	int inc = (divisor < 0.0f) ? -1 : 1;

	for (int y = _from; y != _to; y += inc)
	{
		float t = (y - _from) * divisor;
		CColor pixelColor = LerpColor(cfrom, cto, t);

		float z = Lerp(z1, z2, t);
		DrawVertex_Z(_axis, y, z, pixelColor);
	}
}
// ------------------------------------------------------------------------------------------

void FastDrawLine(const CVertex2& from, const CVertex2& to)
{
	// Get slope and y intercept
	float m = CalcSlope(from.point, to.point);
	float b = GetYIntercept(from.point, m);;

	// Only iterate over x for slopes between 0 and 1
	if (fabs(m) > 1.0f)
	{
		// Cache time divisor so we can use multiplication
		float divisor = CalcTimeDivisor(from.point.y, to.point.y);
		int inc = (divisor < 0.0f) ? -1 : 1;	// +/- direction

		const int y1 = RoundPixel(from.point.y);
		const int y2 = RoundPixel(to.point.y);

		for (int y = y1; y != y2; y += inc)
		{
			int x = RoundPixel((y - b) / m);

			// Calculate how far along the line we are and lerp the colors
			float t = (y - y1) * divisor;
			CColor pixelColor = LerpColor(from.color, to.color, t);
			DrawVertex(x, y, pixelColor);
		}
	}
	else
	{
		// Cache time divisor so we can use multiplication
		float divisor = CalcTimeDivisor(from.point.x, to.point.x);
		int inc = (divisor < 0.0f) ? -1 : 1;	// +/- direction

		const int x1 = RoundPixel(from.point.x);
		const int x2 = RoundPixel(to.point.x);

		for (int x = x1; x != x2; x += inc)
		{
			int y = RoundPixel((m * x) + b);

			// Calculate how far along the line we are and lerp the colors
			float t = (x - x1) * divisor;
			CColor pixelColor = LerpColor(from.color, to.color, t);
			DrawVertex(x, y, pixelColor);
		}
	}
}

void DrawLine(const CVertex2& from, const CVertex2& to)
{
	if (IsHorizontal(from.point, to.point))
	{
		DrawHorizontalLine(from, to);
	}
	else if (IsVertical(from.point, to.point))
	{
		DrawVerticalLine(from, to);
	}
	else
	{
		FastDrawLine(from, to);
	}
}
// ------------------------------------------------------------------------------------------

void DrawLine(const CVector2& from, const CVector2& to, 
			  const CColor& cfrom, const CColor& cto)
{
	DrawLine(CVertex2(from, cfrom), CVertex2(to, cto));
}