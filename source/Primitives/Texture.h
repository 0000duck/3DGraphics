#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Containers/Color.h"
#include "3DGFXTypes.h"

class CTexture
{
public:
	CTexture() : m_Width(0), m_Height(0), m_Texels(NULL),
				 m_UBoundary( Texturing::None ), m_VBoundary( Texturing::None ) {}

	void Clear();

public:
	unsigned int width() const	{ return m_Width; }
	unsigned int height() const	{ return m_Height; }
	void SetDimensions( const unsigned int width, const unsigned int height );
	void SetBoundaries(Texturing::Boundary u, Texturing::Boundary v);

	CColor texel( const unsigned int u, const unsigned int v ) const;
	void SetTexel( const unsigned int u, const unsigned int v, const CColor color );

	Texturing::Boundary uBoundary() const	{ return m_UBoundary; }
	Texturing::Boundary vBoundary() const	{ return m_VBoundary; }

	void SetData( const unsigned int width, const unsigned int height, const void* data );

protected:
	unsigned int m_Width, m_Height;
	CColor *m_Texels;
	Texturing::Boundary m_UBoundary, m_VBoundary;
};

#endif // __TEXTURE_H__