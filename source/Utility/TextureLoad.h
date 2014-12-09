#ifndef __TEXTURELOAD_H__
#define __TEXTURELOAD_H__

class CTexture;

class CTextureLoad
{
public:
	CTextureLoad() {}
	~CTextureLoad() {}

	virtual bool LoadTexture( const CString &filename, CTexture *texture ) = 0;
};

#endif // __TEXTURELOAD_H__
