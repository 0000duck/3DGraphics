#include "stdafx.h"
#include "Transforms.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Matrix33.h"

CVector2 Transform3HC(const CVector2& v, const CMatrix33& m)
{
	CVector3 vtemp(v.x, v.y, 1.0f);
	vtemp = m * vtemp;
	return CVector2(vtemp.x, vtemp.y);
}

CMatrix33 CreateTransformAroundCenter(const CVector2& pivot, const CMatrix33& m)
{
	// A = (-T)RT

	CMatrix33 a = m;

	CMatrix33 toOrigin;	// T
	toOrigin.Identity();
	toOrigin(0, 2) = -pivot.x;
	toOrigin(1, 2) = -pivot.y;

	a *= toOrigin;

	CMatrix33 fromOrigin; // -T
	fromOrigin.Identity();
	fromOrigin(0, 2) = pivot.x;
	fromOrigin(1, 2) = pivot.y;

	a = fromOrigin * a;
	return a;
}