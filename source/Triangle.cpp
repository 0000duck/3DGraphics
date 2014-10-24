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
	CVertex2 p1;
	CVertex2 p2;
	CVertex2 p3;
	SortVerts(p1, p2, p3);

	CLine l1(p1, p2);
	CLine l2(p1, p3);

	// temp: so we can see where the actual edges are
	//l1.Draw();
	//l2.Draw();

	int y = (int)p1.point.y;
	while (y != (int)p2.point.y)
	{
		int x1 = l1.GetMaxLeftX(y);
		int x2 = l2.GetMaxRightX(y);

		CVertex2 v1((float)x1, (float)y, l1.GetColorAtY(y)), 
				 v2((float)x2, (float)y, l2.GetColorAtY(y)); 

		DrawLine(v1, v2);

		y++;
	}
}

void CTriangle::SortVerts(CVertex2& p1, CVertex2& p2, CVertex2& p3)
{
	// Get the index of the point that is the highest on the screen
	const int index = GetTopPointIndex();
	if (index > mVertIndex || mVertIndex < kVerts)
		return;

	p1 = mVerticies[index];
	
	bool p2Occupied = false;
	for (int i=0; i < mVertIndex; ++i)
	{
		if (i != index)
		{
			if (!p2Occupied)
			{
				p2 = mVerticies[i];
				p2Occupied = true;
			}
			else
			{
				p3 = mVerticies[i];
			}
		}
	}
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
			maxy = (int)mVerticies[i].point.y;
			index = i;
		}
	}
	return index;
}