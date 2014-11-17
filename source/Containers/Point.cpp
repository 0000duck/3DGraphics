#include "stdafx.h"
#include "Point.h"
#include "Vertex2.h"
#include "Vector2.h"

Point::Point(int _x, int _y)
	:	x(_x), y(_y)
{
}

Point::Point(float _x, float _y)
{
	x = static_cast<int>(ceilf(_x));
	y = static_cast<int>(ceilf(_y));
}

Point::Point(const CVector2& v)
{
	x = static_cast<int>(ceilf(v.x));
	y = static_cast<int>(ceilf(v.y));
}

Point::Point(const CVertex2& v)
{
	x = static_cast<int>(ceilf(v.point.x));
	y = static_cast<int>(ceilf(v.point.y));
}

Point::Point()
	:	x(0), y(0)
{
}

Point& Point::operator=(const Point& rhs)
{
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
	}
	return *this;
}

Point& Point::operator=(const CVector2& rhs)
{
	x = static_cast<int>(rhs.x);
	y = static_cast<int>(rhs.y);
	return *this;
}

Point& Point::operator=(const CVertex2& rhs)
{
	x = static_cast<int>(rhs.point.x);
	y = static_cast<int>(rhs.point.y);
	return *this;
}
