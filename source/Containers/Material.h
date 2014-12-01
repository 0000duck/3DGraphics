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