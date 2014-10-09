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

class CLine : public CPrimitive
{
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

	// Returns the slope of the line
	float CalcSlope(const Coord2D& p1, const Coord2D& p2);
	
	// Returns the direction of the line
	CVector2 Direction();

protected:
	// Called when fill mode is line
	virtual void DrawSolid();

	// Called when fill mode is point
	virtual void DrawPoints();

	// Returns true if the colors for both verticies aren't the same
	bool DoColorLerp();

private:
	int mVertIndex;					// Current number of verticies
	CVertex2 mVerticies[kVerts];
};

#endif