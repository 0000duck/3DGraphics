#ifndef __COMMON_H__
#define __COMMON_H__

#include "3DGFXTypes.h"
#include <string>
#include <vector>
#include <memory>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float MIN_COLOR = 0.0f;
const float MAX_COLOR = 1.0f;

//====================================================================================================
// Macros
//====================================================================================================

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#if defined(_DEBUG)
	#define AIASSERT(condition, format, ...)\
	{\
		if (!(condition))\
		{\
			va_list va;\
			char buffer[1024];\
			va_start(va, (#format));\
			vsprintf_s(buffer, 1024, (#format), va);\
			va_end(va);\
			std::string message;\
			message += (buffer);\
			message += "\n";\
			_asm {int 3};\
		}\
	}
#else
	#define AIASSERT(...) void(0);
#endif // #if defined(_DEBUG)

#ifdef _DEBUG	
	inline void AIDebugPrint(const wchar_t *pFormat, ...)
	{
		wchar_t buff[8196];
		va_list va;
		va_start(va, pFormat);
		_vstprintf(buff, sizeof(buff), pFormat, va);
		va_end(va);

		::OutputDebugString(buff);
		::OutputDebugString(L"\n");
	}

	#define dbPrintf AIDebugPrint
#else
	#define dbPrintf(...) void(0);
#endif // #ifdef _DEBUG	

//====================================================================================================
// Helper Functions
//====================================================================================================

// Cheeky alternative to: 'using std::literals::string_literals::operator"" s;'
// since VS2012 doesn't support C++14 :(
inline std::string S(const char* s) 
{
	return std::string(s);
}

inline std::wstring WS(const wchar_t* s) 
{
	return std::wstring(s);
}

inline float CalcTimeDivisor(float a, float b)
{
	float divisor = 0.0f;
	float diff = b - a;
	if (diff != 0.0f) {
		divisor = 1.0f / diff;
	}
	return divisor;
}

// Precise method which guarantees p = p1 when t = 1.
inline float Lerp(float p0, float p1, float t)
{
	return (1.0f - t) * p0 + t * p1;
	//return p0 + t * (p1 - p0);
}

inline int RoundPixel(float val)
{
	return static_cast<int>(ceilf(val));
}

// Referencd from Quake III Arena (including original comments because lol)
// http://en.wikipedia.org/wiki/Fast_inverse_square_root
inline float FastInvSqrt(float x)
{
	float xhalf = 0.5f * x;
	int i = *(int*)&x;			// evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);  // what the fuck?
	x = *(float*)&i;
	x = x * (1.5f - (xhalf * x * x));
	return x;
}

#endif // __COMMON_H__
