#include "stdafx.h"
#include "Line.h"
#include "StateManager.h"
#include "Common.h"


CLine::CLine() 
	:	CPrimitive(PrimType::Line)
	,	mVertCount(0)
	,	mSlope(0)
{}

CLine::CLine(const CVertex2& p1, const CVertex2& p2)
	:	CPrimitive(PrimType::Line)
	,	mVertCount(2)
{
	mVertA = p1;
	mVertB = p2;
	mSlope = CalcSlope(p1.point, p2.point);
}

CLine::CLine(const CLine& rhs)
	:	CPrimitive(rhs.mType)
{
	*this = rhs;
}

CLine& CLine::operator=(const CLine& rhs)
{
	if (this != &rhs)
	{
		mVertCount = rhs.mVertCount;
		mVertA = rhs.mVertA;
		mVertB = rhs.mVertB;
	}
	return *this;
}

bool CLine::IsValid() const
{
	// Check that we have the correct number of verticies
	if (mVertCount != kVerts)
	{
		return false;
	}
	return (CPrimitive::IsValid());
}

void CLine::AddVertex(const CVertex2& vert)
{
	if (mVertCount == 0)
		mVertA = vert;
	else if (mVertCount > 0 && mVertCount < kVerts)
		mVertB = vert;
}

const int CLine::VertexCount() const
{
	return mVertCount;
}

const int CLine::MaxVerticies() const
{
	return kVerts;
}

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
		DrawSolid();
		break;
	}
}

void CLine::DrawSolid()
{
	// Cache the points
	CVector2 p1 = mVertA.point;
	CVector2 p2 = mVertB.point;

	// Store vertex colors
	CColor c1 = mVertA.color;
	CColor c2 = mVertB.color;

	// Get slope and y intercept
	float m = CalcSlope(p1, p2);
	float b = p1.y - (m * p1.x);
	float t = 0.0f;
	float divisor = 0.0f;
	int inc = 1;

	// If the slope is greater than 1, we want to iterate over the Y
	if (m > 1)
	{
		// Cache time divisor so we can use multiplication
		float divisor = CalcTimeDivisor(p1.y, p2.y);

		// Check if we need to increment in the positive or negative
		if (divisor < 0.0f)
			inc = -1;

		// Iterate over y pixels
		for (int y = (int)p1.y; y != (int)p2.y; y += inc)
		{
			// Calculate the x
			int x = RoundPixel((y - b) / m);

			// Calculate how far along the line we are and lerp the colors
			t = (y - p1.y) * divisor;
			CColor pixelColor = LerpColor(c1, c2, t);

			DrawVertex(x, y, pixelColor);
		}
	}
	else
	{
		// Cache time divisor
		float divisor = CalcTimeDivisor(p1.x, p2.x);

		// Check if we need to increment in the positive or negative
		if (divisor < 0.0f)
			inc = -1;

		// Iterate over x pixels
		for (int x = (int)p1.x; x != (int)p2.x; x += inc)
		{
			// Calculate the Y
			int y = RoundPixel((m * x) + b);

			// Calculate how far along the line we are and lerp the colors
			t = (x - p1.x) * divisor;
			CColor pixelColor = LerpColor(c1, c2, t);
			
			DrawVertex(x, y, pixelColor);
		}
	}
}

void CLine::DrawPoints()
{
	CColor c1 = mVertA.color;
	CColor c2 = mVertB.color;

	DrawVertex((int)mVertA.point.x, (int)mVertA.point.y, c1);
	DrawVertex((int)mVertB.point.x, (int)mVertB.point.y, c2);
}

bool CLine::DoColorLerp()
{
	// If the colors are the same for both verticies we don't need
	// to interpolate.
	return (mVertA.color != mVertB.color);
}

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

int CLine::CalcY(int x)
{
	float m = CalcSlope(mVertA.point, mVertB.point);
	float b = mVertA.point.y - (m * mVertA.point.x);
	return RoundPixel(m * x + b);
}

int CLine::CalcX(int y)
{
	float m = CalcSlope(mVertA.point, mVertB.point);
	float b = mVertA.point.y - (m * mVertA.point.x);
	return RoundPixel((y - b) / m);
}

int CLine::GetMaxLeftX(int y)
{
	int x = CalcX(y);
	int minX = x, maxX = x;
	int x1 = x, y1 = y;

	do {
		x1--;
		y1 = CalcY(x1);
		if (y1 == y)
			minX = x1;
	} while (y1 == y);

	return minX;
}

int CLine::GetMaxRightX(int y)
{
	int x = CalcX(y);
	int minX = x, maxX = x;
	int x1 = x, y1 = y;

	do {
		x1++;
		y1 = CalcY(x1);
		if (y1 == y)
			maxX = x1;
	} while (y1 == y);

	return maxX;
}

CColor CLine::GetColorAtY(int y)
{
	// Calling CalcTimeDivisor saves us from handling divide by 0
	float divisor = CalcTimeDivisor(mVertA.point.y, mVertB.point.y);

	float t = (y - mVertA.point.y) * divisor;
	return LerpColor(mVertA.color, mVertB.color, t);
}

// Global helper definitions

void DrawLine(const CVertex2& p1, const CVertex2& p2)
{
	CLine line(p1, p2);
	line.Draw();
}

void DrawLine(int x1, int y1, int x2, int y2, const CColor& c1, const CColor& c2)
{
	CVertex2 v1((float)x1, (float)x2, c1), 
			 v2((float)x2, (float)x2, c2); 
	
	DrawLine(v1, v2);
}