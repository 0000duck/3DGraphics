//====================================================================================================
//	File: Line.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Implementation of the Line primitive.
//		Derives from CPrimitive.
//====================================================================================================

#ifndef INCLUDED_LINE_H
#define INCLUDED_LINE_H

#include "Primitive.h"

class CLine : public CPrimitive
{
	friend bool operator==(const CLine& lhs, const CLine& rhs);
	friend bool operator!=(const CLine& lhs, const CLine& rhs);

public:
	// Number of verticies required for this primitive
	static const int kVerts = 2;

	// Constructors
	CLine();
	CLine(float x1, float y1, float x2, float y2, const CColor& c1, const CColor& c2);
	CLine(const CVector2& p1, const CVector2& p2, const CColor& c1, const CColor& c2);
	CLine(const CVertex2& p1, const CVertex2& p2);
	CLine(const CLine& rhs);
	CLine& operator=(const CLine& rhs);

	// Inherited from CPrimitive
	virtual bool IsValid() const;
	virtual void AddVertex(const CVertex2& vert);
	virtual const int VertexCount() const;
	virtual const int MaxVerticies() const;
	virtual void Draw();
	virtual void GetVert(int index, CVertex2& out);
	virtual void SetVert(int index, const CVertex2& v);
	virtual CVector2 GetPivot();
	virtual void Transform(const CMatrix33& tm);

	void SetVerts(const CVertex2& v1, const CVertex2& v2);
	void Ceil();	// Round up all the verticies
	void Floor();	// Round down all the vertices

	// Draws a line between two points with the same x or y value.
	// Skips re-calculating X for each y, so it is slighty faster.
	// Always draws a solid line; ignores fillmode.
	void DrawVertical();
	void DrawHorizontal();

	// Returns the slope of the line
	friend float CalcSlope(const CVector2& p1, const CVector2& p2);
	float CalcSlope() const;
	float CalcInvSlope() const;

	// Helpers
	int CalcY(int x) const;
	int CalcX(int y) const;
	int GetMaxLeftX(int y) const;
	int GetMaxRightX(int y) const;
	CColor GetColorAtY(int y) const;

	float MinX() const;
	float MinY() const;
	float MaxX() const;
	float MaxY() const;

	bool IsVertical() const;
	bool IsHorizontal() const;

protected:
	virtual void DrawSolid();	// Called when fill mode is line
	virtual void DrawPoints();	// Called when fill mode is point

public:
	int mVertCount;		// Number of verticies assigned
	CVertex2 mV1;
	CVertex2 mV2;
};

#endif