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
	static const int MaxVerts = 3;

	CTriangle();

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

	// Returns a vertex that intersects V1V3 on v2.y
	CVertex3 GetSplitPoint(const CVertex3& v1, const CVertex3& v2, const CVertex3& v3);

protected:
	// Called when fill mode is line
	virtual void DrawSolid();

	// Called when fill mode is point
	virtual void DrawPoints();

	// Called when fill mode is fill
	virtual void Fill();

	// Assigns the verts to the params based on ascending order of the y coord.
	void SortVertsY(CVertex3& p1, CVertex3& p2, CVertex3& p3);

	// Draws a flat top or flat bottom triangle
	void DrawSection(const CLine& left, const CLine& right);
	void DrawSection_Phong(const CLine& left, const CLine& right);

//private:
	int mVertIndex;					// Current number of verticies
	CVertex3 mV1;
	CVertex3 mV2;
	CVertex3 mV3;
};

bool IsLeft(const CVertex3& v1, const CVertex3& v2);

#endif