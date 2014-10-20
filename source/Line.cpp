#include "stdafx.h"
#include "Line.h"
#include "StateManager.h"


CLine::CLine() 
	:	CPrimitive(PrimType::Line)
	,	mVertIndex(0)
{}

CLine::CLine(const CVertex2& p1, const CVertex2& p2)
	:	CPrimitive(PrimType::Line)
	,	mVertIndex(2)
{
	mVerticies[0] = p1;
	mVerticies[1] = p2;
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
		// Copy verticies over
		for (int i=0; i < rhs.mVertIndex; ++i)
		{
			mVerticies[i] = rhs.mVerticies[i];
		}
	}
	return *this;
}

bool CLine::IsValid() const
{
	// Check that we have the correct number of verticies
	if (mVertIndex != kVerts)
	{
		return false;
	}
	return (CPrimitive::IsValid());
}

void CLine::AddVertex(const CVertex2& vert)
{
	if (mVertIndex < kVerts)
	{
		mVerticies[mVertIndex++] = vert;
	}
}

const int CLine::VertexCount() const
{
	return mVertIndex;
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
		break;
	}
}

void CLine::DrawSolid()
{
	// Cache the points
	Coord2D p1 = ToCoord2D(mVerticies[0].point);
	Coord2D p2 = ToCoord2D(mVerticies[1].point);

	// Store vertex colors
	CColor c1 = mVerticies[0].color;
	CColor c2 = mVerticies[1].color;
	CColor pixelColor = c1;
	bool lerpcolor = DoColorLerp();

	// Get slope and y intercept
	float m = CalcSlope(p1, p2);
	float b = p1.y - (m * p1.x);
	float t = 0.0f;
	float divisor = 0.0f;

	if (m > 1 || p1.x == p2.x)
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
void CLine::DrawPoints()
{
	Coord2D p1 = ToCoord2D(mVerticies[0].point);
	Coord2D p2 = ToCoord2D(mVerticies[1].point);
	CColor c1 = mVerticies[0].color;
	CColor c2 = mVerticies[1].color;

	DrawVertex(p1.x, p1.y, c1);
	DrawVertex(p2.x, p2.y, c2);
}

bool CLine::DoColorLerp()
{
	// If the colors are the same for both verticies we don't need
	// to interpolate.
	return (mVerticies[0].color != mVerticies[1].color);
}

float CLine::CalcSlope(const Coord2D& p1, const Coord2D& p2)
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
	if (mVertIndex == kVerts)
	{
		CVector2& v1 = mVerticies[0].point;
		CVector2& v2 = mVerticies[1].point;
		return CVector2(v1.x - v2.x, v1.y - v2.y);
	}
	return CVector2(0.0f, 0.0f);
}