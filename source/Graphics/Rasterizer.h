#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include "Containers/Vertex2.h"
#include <vector>

class CRasterizer
{
public:
	static CRasterizer* Instance();
protected:
	CRasterizer() {}
	CRasterizer(const CRasterizer&);
	CRasterizer& operator= (const CRasterizer&);
private:
	static CRasterizer* pinstance;

public:
	void Initialize() {}

	void SetColor(const float r, const float g, const float b);
	void SetColor(const CColor& color);
	void DrawPoint(const int x, const int y);
	void DrawPoint(const float x, const float y);
	void DrawPoint(const float x, const float y, const float r, const float g, const float b);

	void DrawVertex(const CVertex2& vert);
	void DrawVertex(const int x, const int y, const CColor& color);
	void DrawVertex(const float x, const float y, const CColor& color);
	void DrawVertex_ZEnabled(const CVertex2& vert);
	void DrawVertex_ZEnabled(const int x, const int y, const float z, const CColor& color);
};

inline static void DrawVertex(const CVertex2& vert) 
{ 
	CRasterizer::Instance()->DrawVertex(vert); 
}

inline static void DrawVertex(const int x, const int y, const CColor& color) 
{
	CRasterizer::Instance()->DrawVertex(x, y, color); 
}

inline static void DrawVertex(const float x, const float y, const CColor& color) 
{ 
	CRasterizer::Instance()->DrawVertex(x, y, color); 
}

inline static void DrawVertex_Z(const CVertex2& vert) 
{ 
	CRasterizer::Instance()->DrawVertex_ZEnabled(vert); 
}

inline static void DrawVertex_Z(const int x, const int y, const float z, const CColor& color) 
{ 
	CRasterizer::Instance()->DrawVertex_ZEnabled(x, y, z, color); 
}

#endif // __RASTERIZER_H__
