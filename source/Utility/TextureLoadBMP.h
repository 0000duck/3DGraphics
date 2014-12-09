#ifndef __TEXTURELOADBMP_H__
#define __TEXTURELOADBMP_H__

#include "TextureLoad.h"

class CTextureLoadBMP : public CTextureLoad
{
public:
	CTextureLoadBMP() {}
	~CTextureLoadBMP() {}

	bool LoadTexture( const CString &filename, CTexture *texture );
};

#endif // __TEXTURELOADBMP_H__
