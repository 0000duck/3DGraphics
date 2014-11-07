#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float MIN_COLOR = 0.0f;
const float MAX_COLOR = 1.0f;

//====================================================================================================
// Macros
//====================================================================================================

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#if defined(_DEBUG)
	#define ASSERT(condition, format, ...)\
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
			OutputDebugStringA(message.c_str());\
			DebugBreak();\
		}\
	}
#else
	#define ASSERT(condition, format, ...)
#endif

//====================================================================================================
// Helper Functions
//====================================================================================================

inline float CalcTimeDivisor(float a, float b)
{
	float divisor = 0.0f;
	float diff = b - a;
	if (diff != 0.0f) {
		divisor = 1.0f / diff;
	}
	return divisor;
}

inline int RoundPixel(float val)
{
	return static_cast<int>(val + 0.5f);
}

#endif // __COMMON_H__
