#include "stdafx.h"
#include "ZBuffer.h"

ZBuffer::ZBuffer()
	:	mIsset(false)
{
	// mPrecision is multiplied by sizeof(int) to get number of bits to shift by
	mPrecision = ZBUFF_PRECISION / 4;

	// Must be cast to an UINT32 since '1' defaults as signed.
	mShiftVal = static_cast<ZBTYPE>((1 << (sizeof(int) * mPrecision)));
}

ZBuffer::~ZBuffer()
{
}

bool ZBuffer::Init(const std::size_t width, const std::size_t height)
{
	if (!mIsset && width && height)
	{
		mZBuffer.Clear();
		mZBuffer.Resize(width, height, ZBUFF_DEFAULT);
		mIsset = true;
	}
	return mIsset;
}

void ZBuffer::Clear()
{
	mZBuffer.Clear();
	mIsset = false;
}

void ZBuffer::Wipe()
{
	mZBuffer.SetAll(ZBUFF_DEFAULT);
}

std::size_t ZBuffer::Size() const
{
	return mZBuffer.Size();
}

bool ZBuffer::Isset() const
{
	return mIsset;
}

bool ZBuffer::Compare(const int x, const int y, const FLOAT z)
{
	// Convert the float to it's ZBTYPE equivilant by left shifting it <mPrecision> bits
	ZBTYPE zi = static_cast<ZBTYPE>(mShiftVal * z);
	return (zi < mZBuffer.Get(x, y));
}

bool ZBuffer::CompareAndSet(const int x, const int y,const FLOAT z)
{
	ZBTYPE zi =  static_cast<ZBTYPE>(mShiftVal * z);
	if (zi < mZBuffer.Get(x, y))
	{
		// Update that index with the new value
		mZBuffer.Set(x, y, zi);
		return true;
	}
	return false;
}