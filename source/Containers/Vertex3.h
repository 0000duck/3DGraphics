#ifndef INCLUDED_VERTEX4_H
#define INCLUDED_VERTEX4_H

#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Common.h"
#include "Material.h"

struct CVertex3
{
	CColor color;
	CVector4 point;
	CVector3 worldPoint;
	CVector3 normal;
	CMaterial material;

	static CVertex3 lerpResult;

	inline CVertex3() {}
	inline CVertex3(const CVector4& p, const CColor& c)
		:	point(p), color(c) 
	{
	}
	inline CVertex3(const CVector3& p, const CColor& c)
		:	point(p.x, p.y, p.z, 1.0f), color(c) 
	{
	}
	inline CVertex3(const CVector3& p, const CColor& c, const CMaterial& mat, const CVector3& norm)
		:	point(p.x, p.y, p.z, 1.0f), color(c), material(mat), normal(norm)
	{
	}
	inline CVertex3(float x, float y, float z, const CColor& c)
		:	point(x, y, z, 1.0f), color(c) 
	{
	}
	inline CVertex3& operator=(const CVertex3& rhs)
	{
		if (this != &rhs)
		{
			color = rhs.color;
			point = rhs.point;
			worldPoint = rhs.worldPoint;
			normal = rhs.normal;
			material = rhs.material;
		}
		return *this;
	}

	inline CVector3 Get3DPoint() const { return CVector3(point.x, point.y, point.z); }
	inline CVector2 Get2DPoint() const { return CVector2(point.x, point.y); }
};

inline CVertex3 Vertex3Round(const CVertex3 &v)
{
	CVertex3 result(v);
	result.point.x = ceilf(v.point.x);
	result.point.y = ceilf(v.point.y);
	result.point.z = ceilf(v.point.z);
	result.point.w = ceilf(v.point.w);
	return result;
}

inline CVertex3 Vertex3Lerp(const CVertex3 &v1, const CVertex3 &v2, const float t)
{
	CVertex3::lerpResult.point.x = v1.point.x + t * (v2.point.x - v1.point.x);
	CVertex3::lerpResult.point.y = v1.point.y + t * (v2.point.y - v1.point.y);
	CVertex3::lerpResult.point.z = v1.point.z + t * (v2.point.z - v1.point.z);

	CVertex3::lerpResult.color = LerpColor(v1.color, v2.color, t);
	CVertex3::lerpResult.normal = LerpVector3(v1.normal, v2.normal, t);
	CVertex3::lerpResult.worldPoint = LerpVector3(v1.worldPoint, v2.worldPoint, t);
	CVertex3::lerpResult.material = v1.material;	// prevent material from being overwritten
	return CVertex3::lerpResult;
}

#endif // __VERTEX_H__