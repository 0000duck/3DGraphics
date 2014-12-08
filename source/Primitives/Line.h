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
	CLine(const CVector3& p1, const CVector3& p2, const CColor& c1, const CColor& c2);
	CLine(const CVector2& p1, const CVector2& p2, const CColor& c1, const CColor& c2);
	CLine(const CVertex3& p1, const CVertex3& p2);
	CLine(const CLine& other);
	CLine& operator=(const CLine& other);


	// Inherited from CPrimitive
	virtual bool IsValid() const;
	virtual void AddVertex(const CVertex3& vert);
	virtual const int VertexCount() const;
	virtual const int MaxVerticies() const;
	virtual void Draw(FillMode::Mode mode);
	virtual CVector2 GetPivot() const;
	virtual float GetZDepth();
	virtual void Transform(const CMatrix33& tm);
	virtual CVector3 ComputeNormal() const;
	virtual void SetVertexNormals(const CVector3& normal);
	virtual void SetVertexColors(const CColor& color);

	void SetVerts(const CVertex3& v1, const CVertex3& v2);
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
	CVertex3 mFrom;
	CVertex3 mTo;
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

void FastDrawLine(const CVertex3& from, const CVertex3& to);
void DrawLine(const CVertex3& from, const CVertex3& to);

void DrawHorizontalLine(const CVertex3& from, const CVertex3& to);
void DrawHorizontalLine(float fromX, float toX, float y, const CColor& cfrom, const CColor& cto);
void DrawVerticalLine(const CVertex3& from, const CVertex3& to);
void DrawVerticalLine(float fromY, float toY, float x, const CColor& cfrom, const CColor& cto);

void DrawHorizontalLine_Z(const CVertex3& from, const CVertex3& to);
void DrawHorizontalLine_Z(float fromX, float toX, float y, float z1, float z2, const CColor& cfrom, const CColor& cto);
void DrawVerticalLine_Z(const CVertex3& from, const CVertex3& to);
void DrawVerticalLine_Z(float fromY, float toY, float x, float z1, float z2, const CColor& cfrom, const CColor& cto);

void DrawHLine_Z_Phong(const CVertex3& from, const CVertex3& to);

#endif