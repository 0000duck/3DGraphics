#include "StdAfx.h"
#include "Utility/TextureLoadBMP.h"
#include "TextureManager.h"

TextureManager* TextureManager::pinstance = 0;// initialize pointer
TextureManager* TextureManager::Instance () 
{
	if (pinstance == 0)  // is it the first call?
	{  
		pinstance = new TextureManager; // create sole instance
	}
	return pinstance; // address of sole instance
}

void TextureManager::Initialize()
{ 
	ClearTextures();
}

void TextureManager::CleanUp()
{
	ClearTextures();
}

void TextureManager::ClearTextures()
{
	// Delete texture table
	while( m_TextureTable.begin() != m_TextureTable.end() )
    {
		m_TextureTable.begin()->second->Clear();
		delete m_TextureTable.begin()->second;
        m_TextureTable.erase( m_TextureTable.begin() );
    }
}

bool TextureManager::IsTextureLoaded( const int id )
{
	// Check if id already has a texture loaded
	std::map<int, CTexture *>::const_iterator iter;
    iter = m_TextureTable.find( id );
    if( iter != m_TextureTable.end() )
	{
		return true;
	}

	return false;
}

void TextureManager::LoadTexture( const int id, const CString &filename )
{
	// Texture already loaded in this slot
	if ( IsTextureLoaded( id ) )
	{
		return;
	}

	// Check for valid index
	if ( id < TEXTURE_ID_START )
	{
		return;
	}

	// Load texture into table
	CTexture *texture = new CTexture();

	// CMTODO: assuming bmp for now
	CTextureLoadBMP loader;

	if (!loader.LoadTexture( filename, texture ))
	{
		texture->Clear();
	}
	else
	{
		m_TextureTable.insert( std::make_pair( id, texture ) );
	}
}

void TextureManager::SetTextureBoundary(const int id, Texturing::Boundary u, Texturing::Boundary v)
{
	if (!IsTextureLoaded(id))
	{
		return;
	}
	m_TextureTable[id]->SetBoundaries(u, v);
}

void TextureManager::BindTextureCoordinates( float &u, float &v, CTexture *texture )
{
	if ( texture == NULL )
	{
		return;
	}

	switch ( texture->uBoundary() )
	{
		case Texturing::Wrap:
			u = u - (int)u;
			break;
		case Texturing::Clamp:
			u = CLAMP( u, 0.0f, 1.0f );
			break;
	}

	switch ( texture->vBoundary() )
	{
		case Texturing::Wrap:
			v = v - (int)v;
			break;
		case Texturing::Clamp:
			v = CLAMP( v, 0.0f, 1.0f );
			break;
	}
}

CColor TextureManager::NearestNeighborTextureLookup( const int id, const float u, const float v )
{
	// Find texture in texture table
	CTexture *texture = NULL;

	std::map<int, CTexture *>::const_iterator iter;
    iter = m_TextureTable.find( id );
    if( iter != m_TextureTable.end() )
	{
		texture = iter->second;
	}
	else
	{
		return colorBlack;
	}

	// Bind texture coordinates according to texture u,v boundaries
	float uUnit = u;
	float vUnit = v;
	BindTextureCoordinates( uUnit, vUnit, texture );

	// Convert u,v unit coords into u,v int texels
	int uInt = (int)( u * texture->width() );
	int vInt = (int)( v * texture->height() );

	// Return color of texture texel
	return texture->texel( uInt, vInt );
}

