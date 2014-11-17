#ifndef INCLUDED_POINT_H
#define INCLUDED_POINT_H

class CVector2;
struct CVertex2;

class Point
{
public:
	int x, y;

	Point();
	Point(int _x, int _y);
	Point(float _x, float _y);
	Point(const CVector2& v);
	Point(const CVertex2& v);
	inline ~Point() {}

	Point& operator=(const Point& rhs);
	Point& operator=(const CVector2& rhs);
	Point& operator=(const CVertex2& rhs);
};

#endif // #ifndef INCLUDED_POINT_H