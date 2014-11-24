#ifndef INCLUDED_ARRAY2_H
#define INCLUDED_ARRAY2_H

#include <type_traits>
#include <cassert>
#include <iterator>

// ------------------------------------------------------------------------
// Array2 const iterator
// ------------------------------------------------------------------------

template<class _Myarr2>
class Array2_Const_Iterator
	:	std::iterator<std::random_access_iterator_tag, _Myarr2>
{
public:
	typedef Array2_Const_Iterator<_Myarr2> _Myiter;
	typedef std::random_access_iterator_tag iterator_category;

	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef _Myarr2 value_type;
	typedef _Myarr2 * pointer;
	typedef _Myarr2 & reference;

	Array2_Const_Iterator(_Myarr2* ptr = nullptr)
		:	mPtr(ptr)
	{
	}

	reference operator*()
	{
		return (*this->mPtr);
	}

	pointer operator->() const
	{	// Pointer to class object
		return (std::pointer_traits<pointer>::pointer_to(**this));
	}

	_Myiter& operator++()
	{	// Pre-increment
		++this->mPtr;
		return (*this);
	}

	_Myiter operator++(int)
	{	// Post increment
		_Myiter tmp = *this;
		++*this;
		return tmp;
	}

	_Myiter& operator--()
	{	// Pre-decrement
		--this->mPtr;
		return (*this);
	}

	_Myiter operator--(int)
	{	// Post decrement
		_Myiter _Tmp = *this;
		--*this;
		return _Tmp;
	}

	_Myiter& operator+=(difference_type _Off)
	{	// Increment by integer
		mPtr += _Off;
		return (*this);
	}

	_Myiter operator+(difference_type _Off) const
	{	// return this + integer
		_Myiter _Tmp = *this;
		return (_Tmp += _Off);
	}

	_Myiter& operator-=(difference_type _Off)
	{	// decrement by integer
		return (*this += -_Off);
	}

	_Myiter operator-(difference_type _Off) const
	{	// return this - integer
		_Myiter _Tmp = *this;
		return (_Tmp -= _Off);
	}

	difference_type operator-(const _Myiter& _Right) const
	{	// return difference of iterators
		return (this->mPtr - _Right.mPtr);
	}

	reference operator[](difference_type _Off) const
	{	// subscript
		return (*(*this + _Off));
	}

	bool operator==(const _Myiter& _Right) const
	{	// test for iterator equality
		return (this->mPtr == _Right.mPtr);
	}

	bool operator!=(const _Myiter& _Right) const
	{	// test for iterator inequality
		return (!(*this == _Right));
	}

	bool operator<(const _Myiter& _Right) const
	{	// test if this < _Right
		return (this->mPtr < _Right.mPtr);
	}

	bool operator>(const _Myiter& _Right) const
	{	// test if this > _Right
		return (_Right < *this);
	}

	bool operator<=(const _Myiter& _Right) const
	{	// test if this <= _Right
		return (!(_Right < *this));
	}

	bool operator>=(const _Myiter& _Right) const
	{	// test if this >= _Right
		return (!(*this < _Right));
	}

protected:
	pointer mPtr;
};

// ------------------------------------------------------------------------
// Array2 iterator
// ------------------------------------------------------------------------

template<class _Myarr2>
class Array2_Iterator
	:	public Array2_Const_Iterator<_Myarr2>
{
public:
	typedef Array2_Iterator<_Myarr2> _Myiter;
	typedef Array2_Const_Iterator<_Myarr2> _Mybase;
	typedef std::random_access_iterator_tag iterator_category;

	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef _Myarr2 value_type;
	typedef _Myarr2 * pointer;
	typedef _Myarr2 & reference;

	Array2_Iterator(_Myarr2* ptr = nullptr)
		:	mPtr(ptr)
	{
	}

	reference operator*() const
	{
		return ((reference)**(_Mybase*)this);
	}

	pointer operator->() const
	{	// Pointer to class object
		return (std::pointer_traits<pointer>::pointer_to(**this));
	}

	_Myiter& operator++()
	{	// Pre-increment
		++*(_Mybase*)this;
		return (*this);
	}

	_Myiter operator++(int)
	{	// Post increment
		_Myiter tmp = *this;
		++*this;
		return tmp;
	}

	_Myiter& operator--()
	{	// Pre-decrement
		--*(_Mybase*)this;
		return (*this);
	}

	_Myiter operator--(int)
	{	// Post decrement
		_Myiter _Tmp = *this;
		--*this;
		return _Tmp;
	}

	_Myiter& operator+=(difference_type _Off)
	{	// Increment by integer
		*(_Mybase*)this += _Off;
		return (*this);
	}

	_Myiter operator+(difference_type _Off) const
	{	// return this + integer
		_Myiter _Tmp = *this;
		return (_Tmp += _Off);
	}

	_Myiter& operator-=(difference_type _Off)
	{	// decrement by integer
		return (*this += -_Off);
	}

	_Myiter operator-(difference_type _Off) const
	{	// return this - integer
		_Myiter _Tmp = *this;
		return (_Tmp -= _Off);
	}

	difference_type operator-(const _Myiter& _Right) const
	{	// return difference of iterators
		return (*(_Mybase*)this - _Right);
	}

	reference operator[](difference_type _Off) const
	{	// subscript
		return (*(*this + _Off));
	}
};

// ------------------------------------------------------------------------
// Array2 declaration
// ------------------------------------------------------------------------

template<class T>
class Array2
{
	friend class Array2_Iterator<T>;
	friend class Array2_Const_Iterator<T>;

public: // typedefs
	typedef Array2_Iterator<T> iterator;
	typedef Array2_Const_Iterator<T> const_iterator;

	iterator begin()		{ return iterator(&mData[0]); }
	iterator end()			{ return iterator(&mData[mWidth * mHeight]); }
	const_iterator cbegin()	{ return const_iterator(&mData[0]); }
	const_iterator cend()	{ return const_iterator(&mData[mWidth * mHeight]); }

public:	// Constructors
	Array2();
	Array2(std::size_t width, std::size_t height);
	Array2(std::size_t width, std::size_t height, T defVal);
	Array2(const Array2& rhs);
	~Array2();
	Array2& operator=(const Array2& rhs);

public:	// Methods
	void Resize(std::size_t width, std::size_t height);
	void Resize(std::size_t width, std::size_t height, T defVal);
	void Clear();
	inline bool Empty() { return (!mWidth && !mHeight); }

	std::size_t Size() const;
	std::size_t Width() const;
	std::size_t Height() const;

	void SetAll(const T& value);
	void Set(std::size_t x, std::size_t y, const T& value);
	const T& Get(std::size_t x, std::size_t y) const;

	T& operator[](const std::size_t index);
	const T& operator[](const std::size_t index) const;

private:
	T* mData;
	std::size_t mWidth;
	std::size_t mHeight;
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
Array2<T>::Array2(std::size_t width, std::size_t height)
	:	mData(nullptr)
	,	mWidth(width)
	,	mHeight(height)
{
	assert(!std::is_pointer<T>::value);
	assert(width > 0 && height > 0);

	const std::size_t dim = width * height;
	mData = new T[dim];
	for (std::size_t i=0; i < dim; ++i)
	{
		mData[i] = NULL;
	}
}
// ------------------------------------------------------------------------

template< class T >
Array2<T>::Array2(std::size_t width, std::size_t height, T defVal)
	:	mData(nullptr)
	,	mWidth(width)
	,	mHeight(height)
{
	assert(!std::is_pointer<T>::value);
	assert(width > 0 && height > 0);

	const std::size_t dim = width * height;
	mData = new T[dim];
	for (std::size_t i=0; i < dim; ++i)
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
void Array2<T>::Resize(std::size_t width, std::size_t height)
{
	const std::size_t dimension = width * height;
	T* temp = new T[dimension];

	// Nested loops to make offset calculation much easier
	for (std::size_t y=0; y < height; ++y)
	{
		for (std::size_t x=0; x < width; ++x)
		{
			// Manually calculate offset since we're treating a 1D array as 2D
			const std::size_t index = x + (y * width);
			if (x < mWidth && y < mHeight)
			{
				// copy over values from existing array.
				// Existing values retain position in new array unless they exist
				// beyond the new dimensions.
				temp[index] = Get(x, y);
			}
			else
			{
				temp[index] = NULL;
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
void Array2<T>::Resize(std::size_t width, std::size_t height, T defVal)
{
	const std::size_t dimension = width * height;
	T* temp = new T[dimension];

	// Nested loops to make offset calculation much easier
	for (std::size_t y=0; y < height; ++y)
	{
		for (std::size_t x=0; x < width; ++x)
		{
			// Manually calculate offset since we're treating a 1D array as 2D
			const std::size_t index = x + (y * width);
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
std::size_t Array2<T>::Size() const
{
	return mWidth * mHeight;
}
// ------------------------------------------------------------------------

template< class T >
std::size_t Array2<T>::Width() const
{
	return mWidth;
}
// ------------------------------------------------------------------------

template< class T >
std::size_t Array2<T>::Height() const
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
			std::size_t dim = rhs.mWidth * rhs.mHeight;
			mData = new T[dim];
			for (std::size_t i=0; i < dim; ++i)
			{
				mData[i] = rhs.mData[i];
			}
		}
		else
		{
			mData = NULL;
		}
		mWidth = rhs.mWidth;
		mHeight = rhs.mHeight;
	}
	return *this;
}
// ------------------------------------------------------------------------

template< class T >
void Array2<T>::SetAll(const T& value)
{
	if (mData != nullptr)
	{
		const std::size_t sz = Size();
		for (std::size_t i=0; i < sz; ++i)
		{
			mData[i] = value;
		}
	}
}
// ------------------------------------------------------------------------

template< class T >
void Array2<T>::Set(std::size_t x, std::size_t y, const T& value)	
{
	//AIAssertMsg(x < mWidth && y < mHeight, "Array subscript out of range");
	assert(x < mWidth && y < mHeight);
	*(mData + (x + (mWidth * y))) = value;
}
// ------------------------------------------------------------------------

template< class T >
const T& Array2<T>::Get(std::size_t x, std::size_t y) const
{
	//AIAssertMsg(x < mWidth && y < mHeight, "Array subscript out of range");
	assert(x < mWidth && y < mHeight);
	return (*(mData + (x + (mWidth * y))));
}

template< class T >
T& Array2<T>::operator[](const std::size_t index)
{
	return mData[index];
}

template< class T >
const T& Array2<T>::operator[](const std::size_t index) const
{
	return mData[index];
}

#endif