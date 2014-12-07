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

//====================================================================================================
// CLine declaration
//====================================================================================================

class CLine : public CPrimitive
{
public:
	// Number of verticies required for this primitive
	static const int MaxVerts = 2;

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
	virtual void Draw(FillMode::Mode mode);
	virtual CVector2 GetPivot() const;
	virtual float GetZDepth();
	virtual void Transform(const CMatrix33& tm);
	virtual CVector3 ComputeNormal() const;
	virtual void SetVertexNormals(const CVector3& normal);
	virtual void SetVertexColors(const CColor& color);

	void SetVerts(const CVertex2& v1, const CVertex2& v2);
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
	virtual void DrawSolid();	// Called when fill mode is line or fill
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

bool IsVertical(const CVector2& from, const CVector2& to);
bool IsHorizontal(const CVector2& from, const CVector2& to);

float GetYIntercept(const CVector2& from, const float slope);
float GetYIntercept(const int fromX, const int fromY, const float slope);

float CalcSlope(const CVector2& from, const CVector2& to);
float CalcInvSlope(const CVector2& from, const CVector2& to);

void FastDrawLine(const CVertex2& from, const CVertex2& to);
void DrawLine(const CVertex2& from, const CVertex2& to);
void DrawLine(const CVector2& from, const CVector2& to, const CColor& cfrom, const CColor& cto);

void DrawHorizontalLine(const CVertex2& from, const CVertex2& to);
void DrawHorizontalLine(float fromX, float toX, float y, const CColor& cfrom, const CColor& cto);
void DrawVerticalLine(const CVertex2& from, const CVertex2& to);
void DrawVerticalLine(float fromY, float toY, float x, const CColor& cfrom, const CColor& cto);

void DrawHorizontalLine_Z(const CVertex2& from, const CVertex2& to);
void DrawHorizontalLine_Z(float fromX, float toX, float y, float z1, float z2, const CColor& cfrom, const CColor& cto);
void DrawVerticalLine_Z(const CVertex2& from, const CVertex2& to);
void DrawVerticalLine_Z(float fromY, float toY, float x, float z1, float z2, const CColor& cfrom, const CColor& cto);

#endif