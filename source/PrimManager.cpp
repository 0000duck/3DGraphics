#include "Stdafx.h"
#include "PrimManager.h"
#include "Line.h"
#include "Triangle.h"
#include <cassert>
#include <algorithm>

// static singleton member initialization
PrimManager* PrimManager::spInstance = nullptr;

// --------------------------------------------------------------------

// Singleton accessor
PrimManager* PrimManager::Instance()
{
	if (!spInstance)
	{
		spInstance = new PrimManager();
	}
	return spInstance;
}
// --------------------------------------------------------------------

// Default constructor
PrimManager::PrimManager()
	:	mpCurrentPrim(nullptr)
	,	mReadingVerticies(false)
{
}

void PrimManager::AddPrimitive(std::unique_ptr<CPrimitive>& prim)
{
	// Only set the current primitive if it is valid
	if (prim->IsValid())
	{
		// Obtain ownership over the primitive
		mPrimitiveList.push(std::move(prim));
	}
}

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

void PrimManager::EnableReading()
{
	mReadingVerticies = true;
}

void PrimManager::DisableReading()
{
	mReadingVerticies = false;
}

// Adds a vertex to the current primitive
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

void PrimManager::ClearPrimitive()
{
	if (mpCurrentPrim)
	{
		mpCurrentPrim.release();
		mpCurrentPrim = nullptr;
	}
}

void PrimManager::ClearAll()
{
	// Clear out the primitive list and the current primitive
	for (unsigned int i=0; i < mPrimitiveList.size(); ++i)
	{
		mPrimitiveList.pop();
	}
	ClearPrimitive();
}

void PrimManager::DrawAll()
{
	// Check if the current primitive is valid
	VerifyCurrentPrimitive();

	for (unsigned int i=0; i < mPrimitiveList.size(); ++i)
	{
		// Draw the primitive then remove it from the list
		mPrimitiveList.front()->Draw();
		mPrimitiveList.pop();
	}
}

const CPrimitive* PrimManager::GetCurrentPrimitive() const
{
	return mpCurrentPrim.get();
}