#include "stdafx.h"
#include "Line.h"
#include "StateManager.h"


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
		DrawSolid();
		break;
	case FillMode::Fill:
		Fill();
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
	CColor pixelColor = c1;
	bool lerpcolor = DoColorLerp();

	// Get slope and y intercept
	float m = CalcSlope(p1, p2);
	float b = p1.y - (m * p1.x);
	float t = 0.0f;
	float divisor = 0.0f;

	if (p1.x == p2.x)
	{
		DrawHorizontalLine(mVertA, mVertA);
		return;
	}
	else if (p1.y == p2.y)
	{
		DrawVerticalLine(mVertA, mVertB);
		return;
	}

	if (m > 1/* || p1.x == p2.x && p1.y != p2.y*/)
	{
		// Cache time divisor
		int ydiff = p2.y - p1.y;
		if (ydiff) { divisor = 1.0f / ydiff; }

		// Iterate over y pixels
		for (int y = p1.y; y < p2.y; ++y)
		{
			int x = p1.x;
			if (p1.x != p2.x)
				x = RoundPixel((y - b) / m);

			if (lerpcolor)
			{
				// Calculate how far along the line we are
				t = (y - p1.y) * divisor;
				pixelColor = LerpColor(c1, c2, t);
			}
			DrawVertex(x, y, pixelColor);
		}
	}
	else
	{
		int xdiff = p2.x - p1.x;
		if (xdiff) { divisor = 1.0f / xdiff; }

		// Iterate over x pixels
		for (int x = p1.x; x < p2.x; ++x)
		{
			int y = RoundPixel((m * x) + b);
			if (lerpcolor)
			{
				t = (x - p1.x) * divisor;
				pixelColor = LerpColor(c1, c2, t);
			}
			DrawVertex(x, y, pixelColor);
		}
	}
}

void CLine::DrawVerticalLine(const CVertex2& p1, const CVertex2& p2)
{
	int x = p1.point.x;
	int inc = 1;
	if ((p2.point.y - p1.point.y) < 0)
		inc = -1;

	for (int y = p1.point.y; y <= p2.point.y; y += inc)
	{
		DrawVertex(x, y, colorWhite);
	}
}

void CLine::DrawHorizontalLine(const CVertex2& p1, const CVertex2& p2)
{
	int inc = 1;
	if ((p2.point.x - p1.point.x) < 0)
		inc = -1;

	int y = p1.point.y;
	for (int x = p1.point.x; x <= p2.point.x; x += inc)
	{
		DrawVertex(x, y, colorWhite);
	}
}

void CLine::DrawHorizontalLine(int x1, int y1, int x2, int y2)
{
	int inc = 1;
	if ((x2 - x1) < 0)
		inc = -1;

	int y = y1;
	for (int x = x1; x <= x2; x += inc)
	{
		DrawVertex(x, y, colorWhite);
	}
}

void CLine::DrawPoints()
{
	CColor c1 = mVertA.color;
	CColor c2 = mVertB.color;

	DrawVertex(mVertA.point.x, mVertA.point.y, c1);
	DrawVertex(mVertB.point.x, mVertB.point.y, c2);
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

CVector2 CLine::Direction()
{
	if (mVertCount == kVerts)
	{
		CVector2& v1 = mVertA.point;
		CVector2& v2 = mVertB.point;
		return CVector2(v1.x - v2.x, v1.y - v2.y);
	}
	return CVector2(0.0f, 0.0f);
}

int CLine::GetMaxLeftX(int y)
{
	float b = y - (mSlope * mVertA.point.x);
	float slope = CalcSlope(mVertA.point, mVertB.point);
	if (mSlope > 1)
	{
	//	// Only a single point at this Y
		return RoundPixel((y - b) / mSlope);
	}
	return RoundPixel((y - b) / slope);
}

int CLine::GetMaxRightX(int y)
{
	float b = y - (mSlope * mVertA.point.x);
	float slope = CalcSlope(mVertA.point, mVertB.point);
	return RoundPixel((y - b) / slope);
}

void DrawLine(const CVertex2& p1, const CVertex2& p2)
{
	CLine line(p1, p2);
	line.Draw();
}

void DrawLine(int x1, int y1, int x2, int y2)
{
	CVertex2 v1, v2;
	v1.color = colorWhite;
	v1.point.x = x1;
	v1.point.y = y1;

	v2.color = colorWhite;
	v2.point.x = x2;
	v2.point.y = y2;

	DrawLine(v1, v2);
}