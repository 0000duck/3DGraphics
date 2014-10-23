// ----------------------------------------------------------------------------
//	File: Primitive.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Base class for all primitive types.
// ----------------------------------------------------------------------------

#ifndef INCLUDED_PRIMITIVE_H
#define INCLUDED_PRIMITIVE_H

#include "Vertex2.h"
#include "PrimitiveTypes.h"
#include <vector>

struct Coord2D
{
	Coord2D() {}
	Coord2D(int _x, int _y)
		: x(_x), y(_y) {}
	int x;
	int y;
};

Coord2D ToCoord2D(const CVector2& v);

class CPrimitive
{
public:
	CPrimitive(const PrimType::Type type);
	CPrimitive(const int type);

	// Return the primitives type
	const PrimType::Type Type() const;
	
	// Returns true if the primitive is valid
	virtual bool IsValid() const;

	// Adds a vertex to the primitive
	virtual void AddVertex(const CVertex2& vert) = 0;

	// Returns number of verticies the primitive has been assigned
	virtual const int VertexCount() const = 0;

	// Returns the number of verticies required for the primitive
	virtual const int MaxVerticies() const = 0;

	// The primitive's draw logic
	virtual void Draw() = 0;

protected:
	// Draws a single point
	virtual void DrawVertex(const CVertex2& vert);
	virtual void DrawVertex(const int x, const int y, const CColor& color);

	// Draw the primitive with solid edges
	virtual void DrawSolid() = 0;
	// Draw only the verticies
	virtual void DrawPoints() = 0;
	virtual void Fill() {};

protected:
	const PrimType::Type mType;
};

#endif