#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <map>
#include "Primitives/Texture.h"
#include "Containers/Color.h"

class TextureManager
{
public:
	static TextureManager* Instance();
protected:
	TextureManager() {}
	TextureManager(const TextureManager&);
	TextureManager& operator= (const TextureManager&);
private:
	static TextureManager* pinstance;

public:
	enum
	{
		TEXTURE_ID_INVALID = -1,
		TEXTURE_ID_START = 0
	};

public:
	void Initialize();
	void CleanUp();
	void ClearTextures();

	bool IsTextureLoaded(const int id);
	void LoadTexture(const int id, const CString &filename);
	void SetTextureBoundary(const int id, Texturing::Boundary u, Texturing::Boundary v);

	CColor NearestNeighborTextureLookup(const int id, const float u, const float v);

protected:
	void BindTextureCoordinates(float &u, float &v, CTexture *texture);

private:
	std::map<int, CTexture *> m_TextureTable;
};

#endif // __TEXTUREMANAGER_H__
