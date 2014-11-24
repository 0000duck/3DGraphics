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

//struct IDrawMode
//{
//	virtual void operator()(const CVertex2& vert) = 0;
//	virtual void operator()(const int x, const int y, const float z, const CColor& color) = 0;
//};
//
//// Calls Drawvertex as it normally would
//struct DrawDefault : public IDrawMode
//{
//	inline virtual void operator()(const CVertex2& vert) override
//	{ 
//		CRasterizer::Instance()->DrawVertex(vert);
//	}
//	inline virtual void operator()(const int x, const int y, const float z, const CColor& color) override
//	{ 
//		CRasterizer::Instance()->DrawVertex(x, y, color);
//	}
//};
//
//// Used for iterating over y
//struct DrawSwapXY : public IDrawMode
//{
//	inline virtual void operator()(const CVertex2& vert) override
//	{ 
//		CRasterizer::Instance()->DrawVertex(vert.point.y, vert.point.x, vert.color);
//	}
//	inline virtual void operator()(const int x, const int y, const float z, const CColor& color) override
//	{ 
//		CRasterizer::Instance()->DrawVertex(y, x, color);
//	}
//};
//
//struct DrawZEnabled : public IDrawMode
//{
//	inline virtual void operator()(const CVertex2& vert) override
//	{ 
//		CRasterizer::Instance()->DrawVertex_ZEnabled(vert);
//	}
//	inline virtual void operator()(const int x, const int y, const float z, const CColor& color) override
//	{ 
//		CRasterizer::Instance()->DrawVertex_ZEnabled(x, y, z, color);
//	}
//};

#endif // __RASTERIZER_H__
