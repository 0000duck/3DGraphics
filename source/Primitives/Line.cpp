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
	if (mVertCount != kVerts)
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
	else if (mVertCount > 0 && mVertCount < kVerts)
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
	return kVerts;
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

void CLine::Draw()
{
	FillMode::Mode fMode = StateManager::Instance()->GetFillMode();
	switch (fMode)
	{
	case FillMode::Point:
		DrawPoints();
		break;
	case FillMode::Line:
	case FillMode::Fill:
		{
		if (IsVertical()) DrawVertical();
		else if (IsHorizontal()) DrawHorizontal();
		else DrawSolid();
		}
		break;
	}
}
// ------------------------------------------------------------------------------------------

void CLine::DrawSolid()
{
	// Get slope and y intercept
	float m = CalcSlope();
	float b = GetYIntercept(mFrom, m);;

	// Only iterate over x for slopes between 0 and 1
	if (abs(m) > 1)
	{
		const int y1 = RoundPixel(mFrom.point.y);
		const int y2 = RoundPixel(mTo.point.y);
		DrawLine(y1, y2, CalcXIntercept(m, b));
	}
	else
	{
		const int x1 = RoundPixel(mFrom.point.x);
		const int x2 = RoundPixel(mTo.point.x);
		DrawLine(x1, x2, CalcYIntercept(m, b));
	}
}
// ------------------------------------------------------------------------------------------

void CLine::DrawLine(const int _from, const int _to, IInterceptFunctor& getIntercept)
{
	// Cache time divisor so we can use multiplication
	float divisor = CalcTimeDivisor((float)_from, (float)_to);

	// Check if we need to increment in the positive or negative
	int inc = (divisor < 0.0f) ? -1 : 1;

	// Iterate over y pixels
	for (int p1 = _from; p1 != _to; p1 += inc)
	{
		// Calculate the intercept
		int p2 = getIntercept(p1);

		// Calculate how far along the line we are and lerp the colors
		float t = (p1 - _from) * divisor;
		CColor pixelColor = LerpColor(mFrom.color, mTo.color, t);
		getIntercept.DrawPixel(p1, p2, pixelColor);
	}
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
	return ::CalcSlope(mFrom, mTo);
}
// ------------------------------------------------------------------------------------------

float CLine::CalcInvSlope() const
{
	return ::CalcInvSlope(mFrom, mTo);
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

float GetYIntercept(const CVector2& from, const float slope)
{
	return (from.y - (slope * from.x));
}
// ------------------------------------------------------------------------------------------

float GetYIntercept(const CVertex2& from, const float slope)
{
	return (from.point.y - (slope * from.point.x));
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

float CalcSlope(const CVertex2& from, const CVertex2& to)
{
	return CalcSlope(from.point, to.point);
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

float CalcInvSlope(const CVertex2& from, const CVertex2& to)
{
	return CalcInvSlope(from.point, to.point);
}
// ------------------------------------------------------------------------------------------

void DrawHorizontalLine(const CVertex2& from, const CVertex2& to)
{
	DrawHorizontalLine(from.point.x, to.point.x, from.point.y, from.color, to.color);
}
// ------------------------------------------------------------------------------------------

void DrawHorizontalLine(const float fromX, const float toX, const float y, const CColor& cfrom, const CColor& cto)
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
	DrawHorizontalLine(from.point.x, to.point.x, from.point.y, from.color, to.color);
}
// ------------------------------------------------------------------------------------------

void DrawVerticalLine(const float fromY, const float toY, const float x, const CColor& cfrom, const CColor& cto)
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

void DrawHorizontalLine_Z(const float fromX, const float toX, const float y, const float z1, const float z2, const CColor& cfrom, const CColor& cto)
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

void DrawVerticalLine_Z(const float fromY, const float toY, const float x, const float z1, const float z2, const CColor& cfrom, const CColor& cto)
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

void DrawLine(const CVertex2& from, const CVertex2& to)
{
	CLine line(from, to);
	line.Draw();
}
// ------------------------------------------------------------------------------------------

void DrawLine(const CVector2& from, const CVector2& to, 
			  const CColor& cfrom, const CColor& cto)
{
	CLine line(from, to, cfrom, cto);
	line.Draw();
}
// ------------------------------------------------------------------------------------------

void DrawLine(int x1, int y1, int x2, int y2, 
			  const CColor& c1, const CColor& c2)
{
	CLine line((float)x1, (float)y1, (float)x2, (float)y2, c1, c2);
}
// ------------------------------------------------------------------------------------------

void DrawLinef(float x1, float y1, float x2, float y2, 
			  const CColor& c1, const CColor& c2)
{
	CLine line(x1, y1, x2, y2, c1, c2);
}