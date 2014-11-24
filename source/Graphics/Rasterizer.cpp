#include "StdAfx.h"
#include "Rasterizer.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "Utility/MiniMath.h"
#include "Containers/Color.h"
#include "Containers/Vertex2.h"
#include "Viewport.h"

CRasterizer* CRasterizer::pinstance = nullptr;// initialize pointer
CRasterizer* CRasterizer::Instance() 
{
	if (pinstance == nullptr)  // is it the first call?
	{  
		pinstance = new CRasterizer; // create sole instance
	}
	return pinstance; // address of sole instance
}

void CRasterizer::SetColor( const float r, const float g, const float b )
{
	// Set OpenGL color
	glColor3f( r, g, b );
}

void CRasterizer::SetColor( const CColor& color )
{
	glColor3f( color.r, color.g, color.b );
}

void CRasterizer::DrawPoint( const int x, const int y )
{
	// Draw OpenGL pixel
	glBegin( GL_POINTS );
	glVertex2i( x, y );
	glEnd();
}

void CRasterizer::DrawPoint( const float x, const float y )
{
	// Draw OpenGL pixel
	glBegin( GL_POINTS );
	glVertex2i( (int)(x + 0.5f), (int)(y + 0.5f) );
	glEnd();
}

void CRasterizer::DrawPoint( const float x, const float y, const float r, const float g, const float b )
{
	SetColor( r, g, b );
	DrawPoint( x, y );
}

void CRasterizer::DrawVertex(const CVertex2& vert)
{
	SetColor(vert.color);
	DrawPoint(vert.point.x, vert.point.y);
}

void CRasterizer::DrawVertex(const int x, const int y, const CColor& color)
{
	SetColor(color);
	DrawPoint(x, y);
}

void CRasterizer::DrawVertex(const float x, const float y, const CColor& color)
{
	SetColor(color);
	DrawPoint(x, y);
}

void CRasterizer::DrawVertex_ZEnabled(const CVertex2& vert)
{
	if (Viewport::Instance()->CheckZDepth((int)vert.point.x, (int)vert.point.y, vert.z))
	{
		SetColor(vert.color);
		DrawPoint(vert.point.x, vert.point.y);
	}
}

void CRasterizer::DrawVertex_ZEnabled(const int x, const int y, const float z, const CColor& color)
{
	if (Viewport::Instance()->CheckZDepth(x, y, z))
	{
		SetColor(color);
		DrawPoint(x, y);
	}
}