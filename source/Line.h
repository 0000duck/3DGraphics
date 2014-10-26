// ----------------------------------------------------------------------------
//	File: Line.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Implementation of the Line primitive.
//		Derives from CPrimitive.
// ----------------------------------------------------------------------------

#ifndef INCLUDED_LINE_H
#define INCLUDED_LINE_H

#include "Primitive.h"

// Global helpers
void DrawLine(const CVertex2& p1, const CVertex2& p2);
void DrawLine(int x1, int y1, int x2, int y2, const CColor& c1, const CColor& c2);


class CLine : public CPrimitive
{
	friend bool operator==(const CLine& lhs, const CLine& rhs);
	friend bool operator!=(const CLine& lhs, const CLine& rhs);
public:
	// Number of verticies required for this primitive
	static const int kVerts = 2;

	CLine();
	CLine(const CVertex2& p1, const CVertex2& p2);
	CLine(const CLine& rhs);
	CLine& operator=(const CLine& rhs);

	// Inherited from CPrimitive
	virtual bool IsValid() const;
	virtual void AddVertex(const CVertex2& vert);
	virtual const int VertexCount() const;
	virtual const int MaxVerticies() const;
	virtual void Draw();

	// Draws a line between two points with the same x value.
	// Skips re-calculating X for each y, so it is slighty faster.
	void DrawVertical();

	// Returns the slope of the line
	float CalcSlope(const CVector2& p1, const CVector2& p2);

	int CalcY(int x);
	int CalcX(int y);
	int GetMaxLeftX(int y);
	int GetMaxRightX(int y);
	CColor GetColorAtY(int y);

	float MinX();
	float MinY();
	float MaxX();
	float MaxY();

	bool IsVertical();
	bool IsHorizontal();

protected:
	virtual void DrawSolid();	// Called when fill mode is line
	virtual void DrawPoints();	// Called when fill mode is point

	// Returns true if the colors for both verticies aren't the same
	bool DoColorLerp();

private:
	int mVertCount;		// Number of verticies assigned
	CVertex2 mV1;
	CVertex2 mV2;

	float mSlope;
};

#endif