#include "stdafx.h"
#include "Transforms.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix33.h"
#include "Matrix44.h"

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

void TransformAroundCenter(CVector4& point, const CMatrix44& m)
{
	CMatrix44 a = m;

	CMatrix44 toOrigin;	// T
	toOrigin.Identity();
	toOrigin.mV[12] = -point.x;
	toOrigin.mV[13] = -point.y;
	toOrigin.mV[14] = -point.z;

	a *= toOrigin;

	CMatrix44 fromOrigin; // -T
	fromOrigin.Identity();
	toOrigin.mV[12] = point.x;
	toOrigin.mV[13] = point.y;
	toOrigin.mV[14] = point.z;

	a = fromOrigin * a;
	point = m * point;
}