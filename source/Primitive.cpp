#include "stdafx.h"
#include "Primitive.h"
#include "Rasterizer.h"

Coord2D ToCoord2D(const CVector2& v)
{
	return Coord2D
		(
			static_cast<int>(v.x),
			static_cast<int>(v.y)
		);
}

CPrimitive::CPrimitive(const PrimType::Type type) 
	:	mType(type) 
{}

CPrimitive::CPrimitive(const int type) 
	:	mType(PrimType::Type(type)) 
{}

bool CPrimitive::IsValid() const
{ 
	return (PrimType::IsValid(mType));
}

const PrimType::Type CPrimitive::Type() const
{ 
	return mType;
}

void CPrimitive::DrawVertex(const CVertex2& vert)
{
	CRasterizer::Instance()->SetColor(vert.color);
	CRasterizer::Instance()->DrawPoint(vert.point.x, vert.point.y);
}

void CPrimitive::DrawVertex(const int x, const int y, const CColor& color)
{
	CRasterizer::Instance()->SetColor(color);
	CRasterizer::Instance()->DrawPoint(x, y);
}