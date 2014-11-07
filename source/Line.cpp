#include "stdafx.h"
#include "Line.h"
#include "StateManager.h"
#include "Common.h"
#include "Vector3.h"
#include "Matrix33.h"
#include "Transforms.h"


CLine::CLine() 
	:	CPrimitive(PrimType::Line)
	,	mVertCount(0)
	,	mSlope(0)
{}
// ------------------------------------------------------------------------------------------

CLine::CLine(float x1, float y1, float x2, float y2, const CColor& c1, const CColor& c2)
	:	CPrimitive(PrimType::Line)
	,	mVertCount(0)
	,	mSlope(0)
	,	mV1(x1, y1, c1)
	,	mV2(x2, y2, c2)
{
}
// ------------------------------------------------------------------------------------------

CLine::CLine(const CVector2& p1, const CVector2& p2, const CColor& c1, const CColor& c2)
	:	CPrimitive(PrimType::Line)
	,	mVertCount(0)
	,	mSlope(0)
	,	mV1(p1, c1)
	,	mV2(p2, c2)
{
}
// ------------------------------------------------------------------------------------------

CLine::CLine(const CVertex2& p1, const CVertex2& p2)
	:	CPrimitive(PrimType::Line)
	,	mVertCount(2)
	,	mV1(p1)
	,	mV2(p2)
{
	mSlope = CalcSlope(p1.point, p2.point);
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
		mV1 = rhs.mV1;
		mV2 = rhs.mV2;
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
		mV1 = vert;
		mVertCount++;
	}
	else if (mVertCount > 0 && mVertCount < kVerts)
	{
		mV2 = vert;
		mVertCount++;
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

void CLine::GetVert(int index, CVertex2& out)
{
	ASSERT(index >= 0 && index < kVerts);
	if (index == 0)
		out = mV1;
	if (index == 1)
		out = mV2;
}
// ------------------------------------------------------------------------------------------

void CLine::SetVert(int index, const CVertex2& v)
{
	ASSERT(index >= 0 && index < kVerts);
	if (index == 0)
		mV1 = v;
	if (index == 1)
		mV2 = v;
}
// ------------------------------------------------------------------------------------------

CVector2 CLine::GetPivot()
{
	// todo: call get center from bounding box class
	CVector2 pmax(max(mV1.point.x, mV2.point.x), max(mV1.point.y, mV2.point.y));
	CVector2 pmin(min(mV1.point.x, mV2.point.x), min(mV1.point.y, mV2.point.y));

	float midx = (abs(pmax.x) - abs(pmin.x)) * 0.5f;
	float midy = (abs(pmax.y) - abs(pmin.y)) * 0.5f;

	return CVector2(pmin.x + midx, pmin.y + midy);
}
// ------------------------------------------------------------------------------------------

void CLine::Transform(const CMatrix33& tm)
{
	CMatrix33 a = CreateTransformAroundCenter(GetPivot(), tm);

	// Apply transformation matrix to verts
	mV1.point = Transform3HC(mV1.point, tm);
	mV2.point = Transform3HC(mV2.point, tm);
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
		if (!IsVertical())
			DrawSolid();
		else
			DrawVertical();
		break;
	}
}
// ------------------------------------------------------------------------------------------

void CLine::DrawSolid()
{
	// Get slope and y intercept
	float m = CalcSlope(mV1.point, mV2.point);
	float b = mV1.point.y - (m * mV1.point.x);

	// If the slope is greater than 1, we want to iterate over the Y
	if (m > 1)
	{
		const int y1 = RoundPixel(mV1.point.y);
		const int y2 = RoundPixel(mV2.point.y);

		// Cache time divisor so we can use multiplication
		float divisor = CalcTimeDivisor((float)y1, (float)y2);

		// Check if we need to increment in the positive or negative
		int inc = (divisor < 0.0f) ? -1 : 1;

		// Iterate over y pixels
		for (int y = y1; y != y2; y += inc)
		{
			// Calculate the x
			int x = RoundPixel((y - b) / m);

			// Calculate how far along the line we are and lerp the colors
			float t = (y - y1) * divisor;
			CColor pixelColor = LerpColor(mV1.color, mV2.color, t);
			DrawVertex(x, y, pixelColor);
		}
	}
	else
	{
		const int x1 = RoundPixel(mV1.point.x);
		const int x2 = RoundPixel(mV2.point.x);

		// Cache time divisor
		float divisor = CalcTimeDivisor((float)x1, (float)x2);

		// Check if we need to increment in the positive or negative
		int inc = (divisor < 0.0f) ? -1 : 1;

		// Iterate over x pixels
		for (int x = x1; x != x2; x += inc)
		{
			// Calculate the Y
			int y = RoundPixel((m * x) + b);

			// Calculate how far along the line we are and lerp the colors
			float t = (x - x1) * divisor;
			CColor pixelColor = LerpColor(mV1.color, mV2.color, t);
			DrawVertex(x, y, pixelColor);
		}
	}
}
// ------------------------------------------------------------------------------------------

void CLine::DrawVertical()
{
	ASSERT(mV1.point.x == mV2.point.x, "X values don't match; not a vertical line");

	const int x = RoundPixel(mV1.point.x);
	const int y1 = RoundPixel(mV1.point.y);
	const int y2 = RoundPixel(mV2.point.y);

	// Cache time divisor
	float divisor = CalcTimeDivisor((float)y1, (float)y2);

	// Check if we need to increment in the positive or negative
	int inc = (divisor < 0.0f) ? -1 : 1;

	for (int y = y1; y != y2; y += inc)
	{
		float t = (y - y1) * divisor;
		CColor pixelColor = LerpColor(mV1.color, mV2.color, t);
		DrawVertex(x, y, pixelColor);
	}
}
// ------------------------------------------------------------------------------------------

void CLine::DrawHorizontal()
{
	ASSERT(mV1.point.y == mV2.point.y, "Y values don't match; not a horizontal line");

	const int y = RoundPixel(mV1.point.y);
	const int x1 = RoundPixel(mV1.point.x);
	const int x2 = RoundPixel(mV2.point.x);

	// Cache time divisor
	float divisor = CalcTimeDivisor((float)x1, (float)x2);

	// Check if we need to increment in the positive or negative
	int inc = (divisor < 0.0f) ? -1 : 1;

	for (int x = x1; x != x2; x += inc)
	{
		float t = (x - x1) * divisor;
		CColor pixelColor = LerpColor(mV1.color, mV2.color, t);
		DrawVertex(x, y, pixelColor);
	}
}
// ------------------------------------------------------------------------------------------

void CLine::DrawPoints()
{
	DrawVertex((int)mV1.point.x, (int)mV1.point.y, mV1.color);
	DrawVertex((int)mV2.point.x, (int)mV2.point.y, mV2.color);
}
// ------------------------------------------------------------------------------------------

bool CLine::DoColorLerp()
{
	// If the colors are the same for both verticies we don't need
	// to interpolate.
	return (mV1.color != mV2.color);
}
// ------------------------------------------------------------------------------------------

float CLine::CalcSlope(const CVector2& p1, const CVector2& p2)
{
	float m = 0.0f;
	float dy = static_cast<float>(p2.y - p1.y);		// rise
	float dx = static_cast<float>(p2.x - p1.x);		// run
	if (dx)
	{
		m = dy / dx;
	}
	return m;
}
// ------------------------------------------------------------------------------------------

int CLine::CalcY(int x)
{
	float m = CalcSlope(mV1.point, mV2.point);
	if (m == 0.0f)
	{
		// Avoid dividing by 0.
		return NULL;
	}
	float b = mV1.point.y - (m * mV1.point.x);
	return RoundPixel(m * x + b);
}
// ------------------------------------------------------------------------------------------

int CLine::CalcX(int y)
{
	float m = CalcSlope(mV1.point, mV2.point);
	if (m == 0.0f || m == -INT_MAX)
	{
		// 
		return NULL;
	}
	float b = mV1.point.y - (m * mV1.point.x);
	return RoundPixel((y - b) / m);
}
// ------------------------------------------------------------------------------------------

int CLine::GetMaxLeftX(int y)
{
	int x = CalcX(y);
	int minX = x;
	int y1 = y;

	while (y1 == y)
	{
		x--;
		y1 = CalcY(x);
		if (y1 == y)
		{
			minX = x;
		}
	}
	return minX;
}
// ------------------------------------------------------------------------------------------

int CLine::GetMaxRightX(int y)
{
	int x = CalcX(y);
	int maxX = x;
	int y1 = y;

	while (y1 == y)
	{
		x++;
		y1 = CalcY(x);
		if (y1 == y)
		{
			maxX = x;
		}
	}
	return maxX;
}
// ------------------------------------------------------------------------------------------

CColor CLine::GetColorAtY(int y)
{
	// Calling CalcTimeDivisor saves us from handling divide by 0
	float divisor = CalcTimeDivisor(mV1.point.y, mV2.point.y);

	float t = (y - mV1.point.y) * divisor;
	return LerpColor(mV1.color, mV2.color, t);
}
// ------------------------------------------------------------------------------------------

float CLine::MinX()
{
	float x1 = mV1.point.x;
	float x2 = mV2.point.x;
	return (x1 < x2) ? x1 : x2;
}
// ------------------------------------------------------------------------------------------

float CLine::MinY()
{
	float y1 = mV1.point.y;
	float y2 = mV2.point.y;
	return (y1 < y2) ? y1 : y2;
}
// ------------------------------------------------------------------------------------------

float CLine::MaxX()
{
	float x1 = mV1.point.x;
	float x2 = mV2.point.x;
	return (x1 > x2) ? x1 : x2;
}
// ------------------------------------------------------------------------------------------

float CLine::MaxY()
{
	float y1 = mV1.point.y;
	float y2 = mV2.point.y;
	return (y1 > y2) ? y1 : y2;
}
// ------------------------------------------------------------------------------------------

bool CLine::IsVertical()
{
	return (mV1.point.x == mV2.point.x);
}
// ------------------------------------------------------------------------------------------

bool CLine::IsHorizontal()
{
	return (mV1.point.y == mV2.point.y);
}
// ------------------------------------------------------------------------------------------

bool operator==(const CLine& lhs, const CLine& rhs)
{
	if (lhs.mVertCount == rhs.mVertCount &&
		lhs.mV1 == rhs.mV1 &&
		lhs.mV2 == rhs.mV2)
	{
		return true;
	}
	return false;
}
// ------------------------------------------------------------------------------------------

bool operator!=(const CLine& lhs, const CLine& rhs)
{
	return !(lhs == rhs);
}