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
	return (mMin.x < mMax.x) && (mMin.y < mMax.y);
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