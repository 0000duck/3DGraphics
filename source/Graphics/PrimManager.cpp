#include "Stdafx.h"
#include "PrimManager.h"
#include "Primitives/Line.h"
#include "Primitives/Triangle.h"
#include "Primitives/FillModes.h"
#include "Containers/Matrix33.h"
#include "Containers/Vertex3.h"
#include "Utility/Transforms.h"
#include "StateManager.h"
#include "Clipper.h"
#include "MatrixManager.h"
#include "Camera.h"
#include "Viewport.h"
#include "LightManager.h"
#include <algorithm>

// static singleton member initialization
PrimManager* PrimManager::spInstance = nullptr;

// ------------------------------------------------------------------------------------------

// Singleton accessor
PrimManager* PrimManager::Instance()
{
	if (!spInstance)
	{
		spInstance = new PrimManager();
	}
	return spInstance;
}
// ------------------------------------------------------------------------------------------

void PrimManager::DestroyInstance()
{
	if (spInstance)
	{
		delete spInstance;
		spInstance = nullptr;
	}
}
// ------------------------------------------------------------------------------------------

// Default constructor
PrimManager::PrimManager()
	:	mpCurrentPrim(nullptr)
	,	mReadingVerticies(false)
	,	mCurrentNormal(0.0f, 0.1f, 0.0f)
	,	mNormalInitialized(false)
{
}
// ------------------------------------------------------------------------------------------

void PrimManager::Reset()
{
	mpCurrentPrim.release();
	mReadingVerticies = false;
	mPrimitiveList.clear();
	mVertList.clear();
}
// ------------------------------------------------------------------------------------------

void PrimManager::AddPrimitive(std::unique_ptr<CPrimitive>& prim)
{
	// Only set the current primitive if it is valid
	if (prim->IsValid())
	{
		if (!mNormalInitialized)
		{
			// If the normal wasn't provided by the user, then we can compute it
			// now that we have all the primitive's verticies.
			prim->SetVertexNormals(prim->ComputeNormal());
		}

		// Obtain ownership over the primitive
		mPrimitiveList.push_back(std::move(prim));
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::CreatePrimitive(const PrimType::Type primType)
{
	// Delete the current primitive if there is one
	ClearPrimitive();

	switch (primType)
	{
	case PrimType::Point:
		AIASSERT(false, "Point shouldn't be here. fix this");
		break;
	case PrimType::Line:
		mpCurrentPrim.reset(new CLine());
		break;
	case PrimType::Triangle:
		mpCurrentPrim.reset(new CTriangle());
		break;
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::EnableReading()
{
	mReadingVerticies = true;
}
// ------------------------------------------------------------------------------------------

void PrimManager::DisableReading()
{
	mReadingVerticies = false;
}
// ------------------------------------------------------------------------------------------

void PrimManager::SetCurrentNormal(const CVector3& norm)
{
	mCurrentNormal = norm;
	mNormalInitialized = true;
}
// ------------------------------------------------------------------------------------------

void PrimManager::SetMaterial(Material::Type type, const CColor& color)
{
	switch (type)
	{
	case Material::Ambient:
		mCurrentMaterial.ambient = color;
		break;
	case Material::Diffuse:
		mCurrentMaterial.diffuse = color;
		break;
	case Material::Specular:
		mCurrentMaterial.specular = color;
		break;
	case Material::Emissive:
		mCurrentMaterial.emissive = color;
		break;
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::SetMaterialShine(float shine)
{
	mCurrentMaterial.shine = shine;
}
// ------------------------------------------------------------------------------------------

void PrimManager::AddVertex(CVertex3& vert)
{
	if (mReadingVerticies)
	{
		if (mNormalInitialized)
		{
			// Set vert's normal to what was specified by user.
			// If it wasn't provided, it will be calculated when all the verts are added
			vert.normal = mCurrentNormal;
		}
		vert.material = mCurrentMaterial;
		mVertList.push_back(vert);
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::AddVertex(const CVertex2& vert)
{
	if (mReadingVerticies && mpCurrentPrim)
	{
		mpCurrentPrim->AddVertex(vert);

		// Check that the primitive has room for more verticies
		if (mpCurrentPrim->VertexCount() == mpCurrentPrim->MaxVerticies())
		{
			// Get the type of the current primitive
			PrimType::Type pType = mpCurrentPrim->Type();

			// add the current primitive to the render list
			AddPrimitive(mpCurrentPrim);
			
			// Create a new primitive of the same type
			CreatePrimitive(pType);
		}
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::VerifyCurrentPrimitive()
{
	if (mpCurrentPrim)
	{
		// Check that all primitives are valid
		if (!mpCurrentPrim->IsValid())
		{
			// Delete any invalid primitives
			ClearPrimitive();
		}
		else
		{
			// Primitive is valid so add it to the queue
			AddPrimitive(mpCurrentPrim);
		}
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::Apply2DTransformations()
{
	const CMatrix33& transform = MatrixManager::Instance()->GetMatrix2D();
	if (!MatrixManager::Instance()->IsLoaded2D() || transform.IsIdentity())
	{
		// Don't do pointless calculations
		return;
	}

	PrimList::iterator it = mPrimitiveList.begin();
	for (it; it != mPrimitiveList.end(); ++it)
	{
		(*it)->Transform(transform);
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::Apply3DTransformations()
{
	// Cache all our matricies
	const CMatrix44& transform = MatrixManager::Instance()->GetMatrix3D();
	const CMatrix44& WTV = Camera::Instance()->GetWorldToViewMatrix();
	const CMatrix44& projection = Camera::Instance()->GetPerspectiveMatrix();
	const CMatrix44& NDCtoScreen = Viewport::Instance()->GetNDCToScreenMatrix();

	// Create the model view and transform it by the current matrix.
	// Note: since modelview is just an identity matrix we can just assign the transform directly.
	CMatrix44 modelView = WTV * transform;

	bool computeLighting = LightManager::Instance()->SceneHasLights();
	VertList::iterator it = mVertList.begin();
	for (it; it != mVertList.end(); ++it)
	{
		// Apply the transformation to the point
		CVector4 v = modelView * it->point;

		if (computeLighting)
		{
			// Gouraud lighting
			CVector3 v3(v.x, v.y, v.z);		// convert point back to 3D components to get color
			CVertex3 temp(v3, it->color, it->material, it->normal);
			CColor surfaceColor = LightManager::Instance()->GetSurfaceColor(temp);
			it->color *= surfaceColor;
		}

		// Project the point
		v = projection * v;

		// Convert back to legal HC matrix
		if (v.w != 1.0f)
		{
			v /= v.w;
			v.w = 1.0f;
		}

		// Transform the point back to screen space
		v = NDCtoScreen * v;

		// Add the now 2D point to the current primitive type to be drawn
		AddVertex(CVertex2(v.x, v.y, it->color, v.z));
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::CullAndClip()
{
	int sz = mPrimitiveList.size();
	for (int i=sz-1; i >= 0; --i)
	{
		CPrimitive& prim = *mPrimitiveList[i];

		// Check if the primitive needs to be clipped or culled
		eState rc = Clipper::Instance()->ClipPrimitive(&prim);
		switch (rc)
		{
		case Culled:
			// Don't need to draw the primitive; remove it from the list
			mPrimitiveList.erase(mPrimitiveList.begin() + i);
			break;
		}
	}
}
// ------------------------------------------------------------------------------------------

bool CompareZ(PrimPtr& p1, PrimPtr& p2)
{
	return (p1->GetZDepth() < p2->GetZDepth());
}
// ------------------------------------------------------------------------------------------

void PrimManager::DepthSort()
{
	std::sort(mPrimitiveList.begin(), mPrimitiveList.end(), CompareZ);
	//const int sz = mPrimitiveList.size();

}
// ------------------------------------------------------------------------------------------

void PrimManager::ClearPrimitive()
{
	if (mpCurrentPrim)
	{
		mpCurrentPrim.release();
		mpCurrentPrim = nullptr;
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::ClearAll()
{
	mPrimitiveList.clear();
	mVertList.clear();
	ClearPrimitive();
}
// ------------------------------------------------------------------------------------------

void PrimManager::DrawAll()
{
	// Handle all 2D stuff first as any 3D items will not be 
	// in the primitive list at this point.
	//Apply2DTransformations();

	// Transform the 3D verticies which will convert them to their respecting
	// projected 2D counterparts which are added to the primitive list.
	Apply3DTransformations();


	// Remove anything outside the viewport and clip anything extending past it.
	Viewport::Instance()->BackfaceCull(mPrimitiveList);
	CullAndClip();

	DepthSort();

	FillMode::Mode fmode = StateManager::Instance()->GetFillMode();
	for (auto &it : mPrimitiveList)
	{
		if (it->IsValid())
		{
			// Draw the primitive
			it->Draw(fmode);
		}
	}

	// Clear everything now that it has been drawn
	ClearAll();
}
// ------------------------------------------------------------------------------------------

const CPrimitive* PrimManager::GetCurrentPrimitive() const
{
	return mpCurrentPrim.get();
}