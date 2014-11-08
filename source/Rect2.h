#ifndef INLCUDED_RECT2_H
#define INLCUDED_RECT2_H

#include "Line.h"

class CVector2;

class CRect2
{
public:
	CVector2 mMin;
	CVector2 mMax;

    // constructor/destructor
    CRect2();
    CRect2(float l, float t, float r, float b);
	CRect2(const CVector2& min, const CVector2& max);

	void Expand(const CVector2& point);
	bool IsValid() const;

	bool PointInRect(const CVector2& point);

	CLine GetLeftSegment(void) const	{ return CLine(mMin.x, mMin.y, mMin.x, mMax.y, colorWhite, colorWhite); }
	CLine GetRightSegment(void) const	{ return CLine(mMax.x, mMin.y, mMax.x, mMax.y, colorWhite, colorWhite); }
	CLine GetTopSegment(void) const		{ return CLine(mMin.x, mMin.y, mMax.x, mMin.y, colorWhite, colorWhite); }
	CLine GetBottomSegment(void) const	{ return CLine(mMin.x, mMax.y, mMax.x, mMax.y, colorWhite, colorWhite); }

	float GetWidth(void) const					{ return mMax.x - mMin.x; }
	float GetHeight(void) const					{ return mMax.y - mMin.y; }

	int MinXi() const	{ return static_cast<int>(mMin.x); }
	int MaxXi() const	{ return static_cast<int>(mMax.x); }
	int MinYi() const	{ return static_cast<int>(mMin.y); }
	int MaxYi() const	{ return static_cast<int>(mMax.y); }
};

// External helpers
bool IsValid(const CVector2& min, const CVector2& max);
bool IsValid(float l, float t, float r, float b);
bool PointInRect(const CVector2& min, const CVector2& max, const CVector2& p);
bool PointInRect(float l, float t, float r, float b, float p);


#endif
