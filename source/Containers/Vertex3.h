#ifndef INCLUDED_VERTEX4_H
#define INCLUDED_VERTEX4_H

#include "Color.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Common.h"

struct CVertex3
{
	CColor color;
	CVector4 point;

	inline CVertex3() {}
	inline CVertex3(const CVector4& p, const CColor& c)
		:	point(p), color(c) 
	{
	}
	inline CVertex3(const CVector3& p, const CColor& c)
		:	point(p.x, p.y, p.z, 1.0f), color(c) 
	{
	}
	inline CVertex3(float x, float y, float z, const CColor& c)
		:	point(x, y, z, 1.0f), color(c) 
	{
	}

	friend bool operator==(const CVertex3& lhs, const CVertex3& rhs)
	{
		if (lhs.point.x == rhs.point.x &&
			lhs.point.y == rhs.point.y &&
			lhs.point.z == rhs.point.z &&
			lhs.point.w == rhs.point.w &&
			lhs.color == rhs.color)
		{
			return true;
		}
		return false;
	}

	friend bool operator!=(const CVertex3& lhs, const CVertex3& rhs)
	{
		return !(lhs == rhs);
	}
};

inline void Vertex3Round(CVertex3 &v)
{
	v.point.x = (float)RoundPixel(v.point.x);
	v.point.y = (float)RoundPixel(v.point.y);
	v.point.z = (float)RoundPixel(v.point.z);
	v.point.w = (float)RoundPixel(v.point.w);
}

#endif // __VERTEX_H__