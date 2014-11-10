#include "stdafx.h"
#include "Primitives.h"
#include "Graphics/Rasterizer.h"

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

void DrawLinef(float x1, float y1, float x2, float y2, 
			  const CColor& c1, const CColor& c2)
{
	CLine line(x1, y1, x2, y2, c1, c2);
	line.Draw();
}

void DrawLine(const CVector2& p1, const CVector2& p2, 
			  const CColor& c1, const CColor& c2)
{
	CLine line(p1, p2, c1, c2);
	line.Draw();
}

//CVector2 LineIntersect(const CLine& l1, const CLine& l2)
//{
//
//}