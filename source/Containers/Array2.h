#ifndef INCLUDED_ARRAY2_H
#define INCLUDED_ARRAY2_H

#include <type_traits>
#include <cassert>

template< class T >
class Array2
{
public:
	Array2();
	Array2(unsigned int width, unsigned int height, T defVal);
	Array2(const Array2& rhs);
	~Array2();

	// Resizes the array specified and sets new values to the defaultVal
	void Resize(unsigned int width, unsigned int height, T defVal);

	// deletes the array and resets size
	void Clear();
	
	unsigned int Width() const;
	unsigned int Height() const;

	Array2& operator=(const Array2& rhs);

	void Set(unsigned int x, unsigned int y, const T& value);
	const T& Get(unsigned int x, unsigned int y) const;

private:
	T* mData;
	unsigned int mWidth;
	unsigned int mHeight;
};

// ------------------------------------------------------------------------
// Array2 Definitions
// ------------------------------------------------------------------------

template< class T >
Array2<T>::Array2()
	:	mData(nullptr)
	,	mWidth(0)
	,	mHeight(0)
{
	// Disallow pointers because I'm too lazy to make exceptions for them.
	// ie. deleting
	//AIAssertMsg(!std::is_pointer<T>::value, "Pointer to type not allowed");
	assert(!std::is_pointer<T>::value);
}
// ------------------------------------------------------------------------

template< class T >
Array2<T>::Array2(unsigned int width, unsigned int height, T defVal)
	:	mData(nullptr)
	,	mWidth(width)
	,	mHeight(height)
{
	//AIAssertMsg(!std::is_pointer<T>::value, "Pointer to type not allowed");
	//AIAssertMsg(width > 0 && height > 0, "Invalid dimensions");
	assert(!std::is_pointer<T>::value);
	assert(width > 0 && height > 0);


	unsigned int dim = width * height;
	mData = new T[dim];
	for (unsigned int i=0; i < dim; ++i)
	{
		mData[i] = defVal;
	}
}
// ------------------------------------------------------------------------

template< class T >
Array2<T>::Array2(const Array2& rhs)
{
	// = operator is overloaded to do the same thing.
	*this = rhs;
}
// ------------------------------------------------------------------------

template< class T >
Array2<T>::~Array2()
{
	// Cleanup before destroying
	Clear();
}
// ------------------------------------------------------------------------

template< class T >
void Array2<T>::Resize(unsigned int width, unsigned int height, T defVal)
{
	const unsigned int dimension = width * height;
	T* temp = new T[dimension];

	// Nested loops to make offset calculation much easier
	for (unsigned int y=0; y < height; ++y)
	{
		for (unsigned int x=0; x < width; ++x)
		{
			// Manually calculate offset since we're treating a 1D array as 2D
			const unsigned int index = x + (y * width);
			if (x < mWidth && y < mHeight)
			{
				// copy over values from existing array.
				// Existing values retain position in new array unless they exist
				// beyond the new dimensions.
				temp[index] = Get(x, y);
			}
			else
			{
				temp[index] = defVal;
			}
		}
	}
	// Cleanup and assign
	Clear();
	mData = temp;
	temp = nullptr;
	mWidth = width;
	mHeight = height;
}
// ------------------------------------------------------------------------

template< class T >
void Array2<T>::Clear()
{
	if (mWidth > 0 || mHeight > 0)
	{
		delete [] mData;
		mData = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}
// ------------------------------------------------------------------------

template< class T >
unsigned int Array2<T>::Width() const
{
	return mWidth;
}
// ------------------------------------------------------------------------

template< class T >
unsigned int Array2<T>::Height() const
{
	return mHeight;
}
// ------------------------------------------------------------------------

template< class T >
Array2<T>& Array2<T>::operator=(const Array2& rhs)
{
	// Self assignment check. Absolutely necessary for objects with heap allocated members.
	if (this != &rhs)
	{
		if (rhs.mWidth > 0 || rhs.mHeight > 0)
		{
			unsigned int dim = rhs.mWidth * rhs.mHeight;
			mData = new T[dim];
			for (unsigned int i=0; i < dim; ++i)
			{
				mData[i] = rhs.mData[i];
			}
		}
		else
		{
			mData = nullptr;
		}
		mWidth = rhs.mWidth;
		mHeight = rhs.mHeight;
	}
	return *this;
}
// ------------------------------------------------------------------------

template< class T >
void Array2<T>::Set(unsigned int x, unsigned int y, const T& value)	
{
	//AIAssertMsg(x < mWidth && y < mHeight, "Array subscript out of range");
	assert(x < mWidth && y < mHeight);
	*(mData + (x + (mWidth * y))) = value;
}
// ------------------------------------------------------------------------

template< class T >
const T& Array2<T>::Get(unsigned int x, unsigned int y) const
{
	//AIAssertMsg(x < mWidth && y < mHeight, "Array subscript out of range");
	assert(x < mWidth && y < mHeight);
	return (*(mData + (x + (mWidth * y))));
}

#endif