#ifndef __VERTEX2_H__
#define __VERTEX2_H__

#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Material.h"

struct CVertex2
{
	CColor color;
	CVector2 point;
	CVector3 worldPoint;
	CVector3 normal;
	CMaterial material;
	float z;

	CVertex2() {}
	CVertex2(const CVector2& p, const CColor& c)
		:	point(p), z(0.0f), color(c) {}
	CVertex2(float x, float y, const CColor& c, float _z = 0.0f)
		:	point(x, y), z(_z), color(c) {}
	CVertex2(float x, float y, const CColor& c, const CVector3& _normal, float _z = 0.0f)
		:	point(x, y), normal(_normal), z(_z), color(c) {}

	inline void Ceil();		// Round up all the verticies
	inline void Floor();    // Round down all the vertices

	friend bool operator==(const CVertex2& lhs, const CVertex2& rhs)
	{
		if (lhs.point.x == rhs.point.x &&
			lhs.point.y == rhs.point.y &&
			lhs.z == rhs.z &&
			lhs.color == rhs.color)
		{
			return true;
		}
		return false;
	}

	friend bool operator!=(const CVertex2& lhs, const CVertex2& rhs)
	{
		return !(lhs == rhs);
	}
};

inline void Vertex2Round(CVertex2 &v)
{
	// Round up
	v.point.x = ceilf(v.point.x);
	v.point.y = ceilf(v.point.y);
}

inline CVertex2 Vertex2Lerp(const CVertex2 &v1, const CVertex2 &v2, const float t)
{
	CVertex2 result;
	result.point.x = v1.point.x + t * (v2.point.x - v1.point.x);
	result.point.y = v1.point.y + t * (v2.point.y - v1.point.y);
	result.color.r = v1.color.r + t * (v2.color.r - v1.color.r);
	result.color.g = v1.color.g + t * (v2.color.g - v1.color.g);
	result.color.b = v1.color.b + t * (v2.color.b - v1.color.b);
	return result;
}

inline void CVertex2::Ceil()
{
	point.Ceil();
}

inline void CVertex2::Floor()
{
	point.Floor();
}

#endif // __VERTEX_H__