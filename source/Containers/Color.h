#ifndef __COLOR_H__
#define __COLOR_H__

class CColor
{
public:
	CColor() { r = g = b = 0.0f; }
	CColor( const float rIn, const float gIn, const float bIn )
		: r( rIn ), g( gIn ), b( bIn )
	{
		Clamp();
	}

	void Clamp()
	{
		CLAMP(r, 0.0f, 1.0f);
		CLAMP(g, 0.0f, 1.0f);
		CLAMP(b, 0.0f, 1.0f);
	}

	friend CColor Clamp(const CColor& col)
	{
		CColor c(col);
		CLAMP(c.r, 0.0f, 1.0f);
		CLAMP(c.g, 0.0f, 1.0f);
		CLAMP(c.b, 0.0f, 1.0f);
		return c;
	}

	bool IsValid() const
	{
		// Valid range is from 0.0 to 1.0
		return (r >= 0.0f && g >= 0.0f && b >= 0.0f &&
				r <= 1.0f && g <= 1.0f && b <= 1.0f);
	}

	inline void Lerp(const CColor& other, float t);

	friend CColor operator+( const CColor &lhs, const CColor &rhs )
	{
		return CColor( lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b );
	}

	CColor operator+( const CColor &other )
	{
		return CColor( r + other.r, g + other.g, b + other.b );
	}

	CColor operator+=( const CColor &other )
	{
		r += other.r;
		g += other.g;
		b += other.b;
		return *this;
	}

	CColor operator*( const float scalar )
	{
		return CColor( scalar * r, scalar * g, scalar * b );
	}

	CColor operator*=( const CColor &other )
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		return *this;
	}

	friend CColor operator*( const float scalar, const CColor &color )
	{
		return CColor( scalar * color.r, scalar * color.g, scalar * color.b );
	}

	CColor operator*( const CColor &other )
	{
		return CColor( r * other.r, g * other.g, b * other.b );
	}

	friend bool operator==(const CColor& lhs, const CColor& rhs)
	{
		return (lhs.r == rhs.r &&
				lhs.g == rhs.g &&
				lhs.b == rhs.b);
	}

	friend bool operator!=(const CColor& lhs, const CColor& rhs)
	{
		return !(lhs == rhs);
	}

public:
	float r, g, b;
};

inline CColor LerpColor(const CColor& from, const CColor to, const float t)
{
	CColor color;
	color.r = from.r + (t * (to.r - from.r));
	color.g = from.g + (t * (to.g - from.g));
	color.b = from.b + (t * (to.b - from.b));
	return color;
}

// Common colors
const CColor colorBlack( 0.0f, 0.0f, 0.0f );
const CColor colorWhite( 1.0f, 1.0f, 1.0f );
const CColor colorRed( 1.0f, 0.0f, 0.0f );
const CColor colorGreen( 0.0f, 1.0f, 0.0f );
const CColor colorBlue( 0.0f, 0.0f, 1.0f );

#endif // __COLOR_H__