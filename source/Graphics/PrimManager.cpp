#include "Stdafx.h"
#include "PrimManager.h"
#include "Primitives/Line.h"
#include "Primitives/Triangle.h"
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
		spInstance->ClearAll();
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
	mpCurrentPrim.reset();
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
	ShadingMode::Mode shadingmode = StateManager::Instance()->GetShadingMode();
	switch (shadingmode)
	{
	case ShadingMode::None:
	case ShadingMode::Phong:
		TransformNoShading();
		break;
	case ShadingMode::Flat:
		TransformFlatShading();
		break;
	case ShadingMode::Gouraud:
		TransformWithShading();
		break;
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::TransformNoShading()
{
	const TMatrices tm = MatrixManager::Instance()->GetTransformMatricies();

	// Since we don't need to worry about lighting, we can combine the WTV and local to world
	CMatrix44 modelview = tm.worldToView * tm.localToWorld;
	for (auto vert : mVertList)
	{
		// Transform from local to world to camera
		CVector4 vWorld = tm.localToWorld * vert.point;
		CVector3 worldNorm = tm.localToWorld.TransformNormal(vert.normal);

		CVector4 v =  tm.worldToView * vWorld;
		v = tm.projection * v;	// Project the point
		v = tm.ndcToScreen * v;	// Transform the point back to screen space

		// Add the now 2D point to the current primitive type to be drawn
		CVertex2 vert2(v.x, v.y, vert.color, worldNorm, v.z);
		vert2.worldPoint = vWorld.ToV3();	// store original world position
		vert2.material = vert.material;
		AddVertex(vert2);
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::TransformWithShading()
{
	const TMatrices tm = MatrixManager::Instance()->GetTransformMatricies();
	LightManager& lightManager = *LightManager::Instance();

	for (auto vert : mVertList)
	{
		// Put point and normal into world space.
		CVector4 v = tm.localToWorld * vert.point;
		CVector3 worldNorm = tm.localToWorld.TransformNormal(vert.normal);

		// Get 3D components for lighting calculations
		CVertex3 temp(v.ToV3(), vert.color, vert.material, worldNorm);
		CColor lighting = lightManager.ComputeLighting(temp);
		vert.color *= lighting;	// Apply the lighting

		v = tm.worldToView * v;	// Transform into camera space
		v = tm.projection * v;	// Project the point
		v = tm.ndcToScreen * v;	// Transform the point back to screen space

		// Add the now 2D point to the current primitive type to be drawn
		CVertex2 vert2(v.x, v.y, vert.color, vert.normal, v.z);
		vert2.worldPoint = vert.point.ToV3();	// store original world position
		vert2.material = vert.material;
		AddVertex(vert2);
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::TransformFlatShading()
{
	const TMatrices tm = MatrixManager::Instance()->GetTransformMatricies();
	LightManager& lightManager = *LightManager::Instance();

	int vertCount = 0;
	CColor currentLighting;
	int numVerts = mpCurrentPrim->MaxVerticies();

	for (auto vert : mVertList)
	{
		// Put point and normal into world space.
		CVector4 v = tm.localToWorld * vert.point;
		CVector3 worldNorm = tm.localToWorld.TransformNormal(vert.normal);

		// Get 3D components for lighting calculations
		CVertex3 temp(v.ToV3(), vert.color, vert.material, worldNorm);

		// Only compute lighting when we move to a new face
		if ((vertCount % numVerts) == 0)
		{
			currentLighting = lightManager.ComputeLighting(temp);
		}
		// Apply the lighting
		vert.color *= currentLighting;
		++vertCount;

		v = tm.worldToView * v;	// Transform into camera space
		v = tm.projection * v;	// Project the point
		v = tm.ndcToScreen * v;	// Transform the point back to screen space

		// Add the now 2D point to the current primitive type to be drawn
		CVertex2 vert2(v.x, v.y, vert.color, vert.normal, v.z);
		vert2.worldPoint = vert.point.ToV3();	// store original world position
		vert2.material = vert.material;
		AddVertex(vert2);
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
}
// ------------------------------------------------------------------------------------------

void PrimManager::ClearPrimitive()
{
	if (mpCurrentPrim)
	{
		mpCurrentPrim.reset();
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