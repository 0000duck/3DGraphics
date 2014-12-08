#ifndef INCLUDED_MATERIAL_H
#define INCLUDED_MATERIAL_H

#include "Containers/Color.h"

struct CMaterial
{
	CColor emissive;
	CColor ambient;
	CColor diffuse;
	CColor specular;
	float shine;

	CMaterial& operator=(const CMaterial& rhs)
	{
		emissive = rhs.emissive;
		ambient = rhs.ambient;
		diffuse = rhs.diffuse;
		specular = rhs.specular;
		shine = rhs.shine;
		return *this;
	}
};

namespace Material
{
	enum Type
	{
		WorldAmbient,
		Ambient,
		Diffuse,
		Specular,
		Emissive
	};
}

#endif