#ifndef INCLUDED_PRIMITIVES_H
#define INCLUDED_PRIMITIVES_H

// Includes
#include "Line.h"
#include "Triangle.h"
#include "FillModes.h"

// Helper functions
void DrawLine(const CVertex2& p1, const CVertex2& p2);
void DrawLine(const CVector2& p1, const CVector2& p2, 
			  const CColor& c1=colorWhite, const CColor& c2=colorWhite);
void DrawLine(int x1, int y1, int x2, int y2, 
			  const CColor& c1=colorWhite, const CColor& c2=colorWhite);
void DrawLinef(float x1, float y1, float x2, float y2, 
			  const CColor& c1=colorWhite, const CColor& c2=colorWhite);

CVector2 LineIntersect(const CLine& l1, const CLine& l2);

#endif