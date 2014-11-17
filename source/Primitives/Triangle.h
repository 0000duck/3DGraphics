//====================================================================================================
//	File: Triangle.h
//	Created by: Tyler Staples
//	Date created: 7/10/2014
//	Description: 
//		Implementation of the Triangle primitive.
//		Derives from CPrimitive.
//====================================================================================================

#ifndef INCLUDED_TRIANGLE_H
#define INCLUDED_TRIANGLE_H

#include "Primitive.h"
#include <vector>

class CLine;

class CTriangle : public CPrimitive
{
public:
	// Number of verticies required for this primitive
	static const int kVerts = 3;

	CTriangle();
	CTriangle(const CTriangle& rhs);
	CTriangle& operator=(const CTriangle& rhs);

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

protected:
	// Called when fill mode is line
	virtual void DrawSolid();

	// Called when fill mode is point
	virtual void DrawPoints();

	// Called when fill mode is fill
	virtual void Fill();

	// Assigns the verts to the params based on ascending order of the y coord.
	void SortVertsY(CVertex2& p1, CVertex2& p2, CVertex2& p3);
	void SortVertsX(CVertex2& p1, CVertex2& p2, CVertex2& p3);

private:
	int mVertIndex;					// Current number of verticies
	CVertex2 mV1;
	CVertex2 mV2;
	CVertex2 mV3;
};

#endif