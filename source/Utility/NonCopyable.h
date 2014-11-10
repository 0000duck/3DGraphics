//====================================================================================================
// Filename:	NonCopyable.h
// Created by:	Tyler Staples
// Created on:	04/11/2014
// Description:	Base class for non-copyable types.
//====================================================================================================

#ifndef INCLUDED_NONCOPYABLE_H
#define INCLUDED_NONCOPYABLE_H

class NonCopyable
{
public:
	NonCopyable(){}
	~NonCopyable(){}

private:
	NonCopyable(const NonCopyable&);
	NonCopyable& operator=(const NonCopyable&);
};


#endif // #ifndef INCLUDED_NONCOPYABLE_H