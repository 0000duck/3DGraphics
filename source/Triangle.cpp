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