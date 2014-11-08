#include "StdAfx.h"
#include "Rect2.h"
#include "Vector2.h"
#include "MiniMath.h"

CRect2::CRect2()
	:	mMin(FLT_MAX, FLT_MAX)
	,	mMax(-FLT_MAX, -FLT_MAX)
{
}

CRect2::CRect2(float l, float t, float r, float b)
	:	mMin(l, t)
	,	mMax(r, b)
{
}

CRect2::CRect2(const CVector2& min, const CVector2& max)
	:	mMin(min)
	,	mMax(max)
{
}

void CRect2::Expand(const CVector2& point)
{
	mMin.x = min(mMin.x, point.x);
	mMin.y = min(mMin.y, point.y);
	mMax.x = max(mMax.x, point.x);
	mMax.y = max(mMax.y, point.y);
}

bool CRect2::IsValid() const
{
	return ((mMin.x < mMax.x) && (mMin.y < mMax.y));
}

bool CRect2::PointInRect(const CVector2& point)
{
	if (point.x > mMax.x || point.x < mMin.x ||
		point.y > mMax.y || point.y < mMin.y)
	{
		return false;
	}
	return true;
}

// External helpers

bool IsValid(const CVector2& min, const CVector2& max)
{
	return ((min.x < max.x) && (min.y < max.y));
}

bool IsValid(float l, float t, float r, float b)
{
	return ((l < r) && (t < b));
}

bool PointInRect(const CVector2& min, const CVector2& max, const CVector2& p)
{
	if (p.x > max.x || p.x < min.x ||
		p.y > max.y || p.y < min.y)
	{
		return false;
	}
	return true;
}

bool PointInRect(float l, float t, float r, float b, float p)
{
	if (p > r || p < l || p > b || p < t)
	{
		return false;
	}
	return true;
}