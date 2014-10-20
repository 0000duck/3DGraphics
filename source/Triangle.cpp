#include "stdafx.h"
#include "Triangle.h"
#include "Rasterizer.h"
#include "StateManager.h"
#include "Line.h"

CTriangle::CTriangle() 
	: CPrimitive(PrimType::Triangle)
	, mVertIndex(0)
{
}

CTriangle::CTriangle(const CTriangle& rhs)
	:	CPrimitive(rhs.mType)
{
	*this = rhs;
}

CTriangle& CTriangle::operator=(const CTriangle& rhs)
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

bool CTriangle::IsValid() const
{
	// Check that we have the correct number of verticies
	if (mVertIndex != kVerts)
	{
		return false;
	}
	return (CPrimitive::IsValid());
}

void CTriangle::AddVertex(const CVertex2& vert)
{
	if (mVertIndex < kVerts)
	{
		mVerticies[mVertIndex++] = vert;
	}
}

const int CTriangle::VertexCount() const
{
	return mVertIndex;
}

const int CTriangle::MaxVerticies() const
{
	return kVerts;
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

void CTriangle::DrawSolid()
{
	// Cache the points
	CVertex2 p1 = mVerticies[0];
	CVertex2 p2 = mVerticies[1];
	CVertex2 p3 = mVerticies[2];

	CLine l1(p1, p2);
	CLine l2(p2, p3);
	CLine l3(p1, p3);

	l1.Draw();
	l2.Draw();
	l3.Draw();
}

void CTriangle::DrawPoints()
{
	CVertex2 p1 = mVerticies[0];
	CVertex2 p2 = mVerticies[1];
	CVertex2 p3 = mVerticies[2];

	DrawVertex(p1);
	DrawVertex(p2);
	DrawVertex(p3);
}

void CTriangle::Fill()
{
	// Find the point in our list of verts that has the lowest Y
	const int index = GetTopPointIndex();
	if (index > mVertIndex || mVertIndex < kVerts)
		return;

	CVertex2 p1 = mVerticies[index];
	CVertex2 p2;
	CVertex2 p3;
	
	// TODO: Do this better
	if (index == 0)
	{
		p2 = mVerticies[1];
		p3 = mVerticies[2];
	}
	else if (index == 1)
	{
		p2 = mVerticies[0];
		p3 = mVerticies[2];
	}
	else if (index == 2)
	{
		p2 = mVerticies[0];
		p3 = mVerticies[1];
	}

	CLine l1(p1, p2);
	CLine l2(p1, p3);

	int y = p1.point.y;
	while (y != p2.point.y && y != p3.point.y)
	{
		int leftX = l1.GetMaxLeftX(y);
		int rightX = l2.GetMaxRightX(y);
		l1.DrawHorizontalLine(leftX, y, rightX, y);
		++y;
	}

	//int riseA = p2.point.y - p1.point.y;
	//int riseB = p3.point.y - p1.point.y;
	//int runA = p2.point.x - p1.point.x;
	//int runB = p3.point.x - p1.point.x;
}

int CTriangle::GetTopPointIndex()
{
	int index = 0;
	int maxy = INT_MAX;
	for (int i=0; i < mVertIndex; ++i)
	{
		// 0,0 is top left, so a higher Y would mean it has a lower value
		if (mVerticies[i].point.y < maxy)
		{
			maxy = mVerticies[i].point.y;
			index = i;
		}
	}
	return index;
}