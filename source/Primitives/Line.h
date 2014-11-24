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
#include "Graphics/Rasterizer.h"

// Base functor
struct IInterceptFunctor
{
	float m, b;

	inline IInterceptFunctor(const float _m, const float _b)
		:	m(_m), b(_b)
	{
	}
	virtual int operator()(int coord) const = 0;
	virtual void DrawPixel(int p1, int p2, const CColor& c) = 0;
};

// Derived functor for calculating X intercept
struct CalcXIntercept : public IInterceptFunctor
{
	inline CalcXIntercept(const float _m, const float _b)
		:	IInterceptFunctor(_m, _b)
	{
	}

	inline virtual int operator()(int y) const
	{
		// x = y - b / m
		return RoundPixel((y - b) / m);
	}

	inline virtual void DrawPixel(int p1, int p2, const CColor& c)
	{
		// Switches p1 and p2 since they will be passed in to this function as y, x
		CRasterizer::Instance()->DrawVertex(p2, p1, c);
	}
};

// Derived functor for calculating Y intercept
struct CalcYIntercept : public IInterceptFunctor
{
	inline CalcYIntercept(const float _m, const float _b)
		:	IInterceptFunctor(_m, _b)
	{
	}

	inline virtual int operator()(int x) const
	{
		// y = mx + b
		return RoundPixel((m * x) + b);
	}

	inline virtual void DrawPixel(int p1, int p2, const CColor& c)
	{
		CRasterizer::Instance()->DrawVertex(p1, p2, c);
	}
};

//====================================================================================================
// CLine declaration
//====================================================================================================

class CLine : public CPrimitive
{
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
	virtual CVector2 GetPivot();
	virtual float GetZDepth();
	virtual void Transform(const CMatrix33& tm);

	void SetVerts(const CVertex2& v1, const CVertex2& v2);
	void DrawLine(const int from, const int to, IInterceptFunctor& getIntercept);
	void DrawHorizontal();
	void DrawVertical();

	// Internal Helpers
	float CalcSlope() const;
	float CalcInvSlope() const;
	int CalcY(int x) const;
	int CalcX(int y) const;
	CColor GetColorAtY(int y) const;
	bool IsVertical() const;
	bool IsHorizontal() const;

protected:
	virtual void DrawSolid();	// Called when fill mode is line
	virtual void DrawPoints();	// Called when fill mode is point

public:
	int mVertCount;		// Number of verticies assigned
	CVertex2 mFrom;
	CVertex2 mTo;
	float mSlope;
};

//====================================================================================================
// Extern Helpers
//====================================================================================================

float GetYIntercept(const CVector2& from, const float slope);
float GetYIntercept(const CVertex2& from, const float slope);
float GetYIntercept(const int fromX, const int fromY, const float slope);

float CalcSlope(const CVector2& from, const CVector2& to);
float CalcSlope(const CVertex2& from, const CVertex2& to);
float CalcInvSlope(const CVector2& from, const CVector2& to);
float CalcInvSlope(const CVertex2& from, const CVertex2& to);

void DrawLine(const CLine& line);
void DrawLine(const CVertex2& from, const CVertex2& to);
void DrawLine(const CVector2& from, const CVector2& to, const CColor& cfrom, const CColor& cto);
void DrawLine(int x1, int y1, int x2, int y2, const CColor& c1, const CColor& c2);
void DrawLinef(float x1, float y1, float x2, float y2, const CColor& c1, const CColor& c2);

void DrawLine_ZEnabled(const CLine& line);
void DrawLine_ZEnabled(const CVertex2& from, const CVertex2& to);

void DrawStraightLine(const float from, const float to, const float axis, const CColor& cfrom, const CColor& cto, IDrawMode& drawpoint=DrawDefault());
void DrawStraightLine_ZEnabled(const float from, const float to, const float axis, const float z1, const float z2, const CColor& cfrom, const CColor& cto);

void DrawHorizontalLine_ZEnabled(const CVertex2& from, const CVertex2& to);
void DrawHorizontalLine_ZEnabled(const float fromX, const float toX, const float y, const CColor& cfrom, const CColor& cto);
void DrawVerticalLine_ZEnabled(const CVertex2& from, const CVertex2& to);
void DrawVerticalLine_ZEnabled(const float fromY, const float toY, const float x, const CColor& cfrom, const CColor& cto);

#endif