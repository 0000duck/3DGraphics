#include "Stdafx.h"
#include "PrimManager.h"
#include "Line.h"
#include "Triangle.h"
#include "Clipper.h"
#include "MatrixManager.h"
#include "Matrix33.h"
#include "Vertex3.h"
#include <cassert>
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

// Default constructor
PrimManager::PrimManager()
	:	mpCurrentPrim(nullptr)
	,	mReadingVerticies(false)
{
}
// ------------------------------------------------------------------------------------------

void PrimManager::AddPrimitive(std::unique_ptr<CPrimitive>& prim)
{
	// Only set the current primitive if it is valid
	if (prim->IsValid())
	{
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

void PrimManager::AddVertex(const CVertex3& vert)
{
	if (mReadingVerticies)
	{
		mVertList.push_back(vert);
	}
}
// ------------------------------------------------------------------------------------------

void PrimManager::AddVertex(const CVertex2& vert)
{
	if (mReadingVerticies && mpCurrentPrim)
	{
		// Check that the primitive has room for more verticies
		if (mpCurrentPrim->VertexCount() < mpCurrentPrim->MaxVerticies())
		{
			mpCurrentPrim->AddVertex(vert);
		}
		else
		{
			// Get the type of the current primitive
			PrimType::Type pType = mpCurrentPrim->Type();

			// add the current primitive to the render list
			AddPrimitive(mpCurrentPrim);
			
			// Create a new primitive of the same type
			CreatePrimitive(pType);

			// Recall this function to do necessary checks
			AddVertex(vert);
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

void PrimManager::ApplyTransformations()
{
	const CMatrix33& transform = MatrixManager::Instance()->GetMatrix2D();
	if (!MatrixManager::Instance()->IsLoaded2D() ||
		transform.IsIdentity())
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
	// Clear out the primitive list and the current primitive
	mPrimitiveList.clear();;
	mVertList.clear();
	ClearPrimitive();
}
// ------------------------------------------------------------------------------------------

void PrimManager::DrawAll()
{
	// Check if the current primitive is valid
	VerifyCurrentPrimitive();

	// Apply any transformations to the primitives
	ApplyTransformations();

	// Remove anything outside the viewport and clip anything extending past it.
	CullAndClip();

	PrimList::iterator it = mPrimitiveList.begin();
	for (it; it != mPrimitiveList.end(); ++it)
	{
		// Draw the primitive
		(*it)->Draw();
	}

	// Clear everything now that it has been drawn
	ClearAll();
}
// ------------------------------------------------------------------------------------------

const CPrimitive* PrimManager::GetCurrentPrimitive() const
{
	return mpCurrentPrim.get();
}