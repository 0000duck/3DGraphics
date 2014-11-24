//====================================================================================================
//	File: ZBuffer.h
//	Created by: Tyler Staples
//	Date created: 24/11/2014
//	Description: 
//		Wrapper for zbuffer functionality.
//====================================================================================================

#ifndef INCLUDED_ZBUFFER_H
#define INCLUDED_ZBUFFER_H
#pragma once

#define ZBUFF32_PRECISION 32
#define ZBUFF32_DEFAULT UINT32_MAX

#define ZBUFF_PRECISION ZBUFF32_PRECISION
#define ZBUFF_DEFAULT ZBUFF32_DEFAULT
typedef UINT32 ZBTYPE;

#include "Utility/NonCopyable.h"
#include "Array2.h"

class ZBuffer : private NonCopyable
{
public:
	ZBuffer();
	~ZBuffer();

	bool Init(const std::size_t width, const std::size_t height);
	void Clear();
	void Wipe();
	bool Isset() const;
	std::size_t Size() const;

	bool Compare(const int x, const int y, const FLOAT z);
	bool CompareAndSet(const int x, const int y, const FLOAT z);

private:
	Array2<ZBTYPE> mZBuffer;
	int mPrecision;
	ZBTYPE mShiftVal;
	bool mIsset;
};

#endif