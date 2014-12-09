#include "StdAfx.h"
#include "Texture.h"

void CTexture::Clear()
{
	m_Width = 0;
	m_Height = 0;
	if ( m_Texels != NULL )
	{
		delete [] m_Texels;
		m_Texels = NULL;
	}
}

void CTexture::SetDimensions( const unsigned int width, const unsigned int height )
{
	// Only allow dimensions to be set if texel array hasn't been created
	if ( width == 0 || height == 0 || m_Texels != NULL )
	{
		return;
	}

	m_Width = width;
	m_Height = height;

	m_Texels = new CColor [m_Width * m_Height];
}

void CTexture::SetBoundaries(Texturing::Boundary u, Texturing::Boundary v)
{
	if (IsValidType(u, Texturing::NumModes))
		m_UBoundary = u;
	if (IsValidType(v, Texturing::NumModes))
		m_VBoundary = v;
}

CColor CTexture::texel( const unsigned int u, const unsigned int v ) const
{
	if ( u >= 0 && u < m_Width &&
		 v >= 0 && v < m_Height )
	{
		return m_Texels[v * m_Width + u];
	}

	return colorBlack;
}

void CTexture::SetTexel( const unsigned int u, const unsigned int v, const CColor color )
{
	if ( u >= 0 && u < m_Width &&
		 v >= 0 && v < m_Height && m_Texels != NULL )
	{
		m_Texels[v * m_Width + u] = color;
	}
}

void CTexture::SetData( const unsigned int width, const unsigned int height, const void* data )
{
	if ( width == 0 || height == 0 || data == NULL )
	{
		return;
	}

	m_Width = width;
	m_Height = height;

	m_Texels = new CColor [m_Width * m_Height];
	unsigned int numBits = m_Width * m_Height * 3;
	memcpy( m_Texels, data, numBits );
}
