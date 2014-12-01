//====================================================================================================
//	File: PrimManager.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Keeps track of the current primitive being drawn and its verticies.
//		To use this class, use the static accessor by calling StateManager::Instance().
//====================================================================================================

#ifndef INCLUDED_PRIMMANAGER_H
#define INCLUDED_PRIMMANAGER_H
#pragma once

#include "Utility/NonCopyable.h"
#include "Primitives/Primitive.h"
#include "Containers/Material.h"
#include <vector>
#include <memory>

struct CVertex3;

typedef std::unique_ptr<CPrimitive> PrimPtr;
typedef std::vector<PrimPtr> PrimList;
typedef std::vector<CVertex3> VertList;

class PrimManager : private NonCopyable
{
	// Constructors
	PrimManager();

public:
	// Singleton accessor
	static PrimManager* Instance();

	// Destroys the current instance of this class.
	static void DestroyInstance();

	// Resets all data members to default values
	void Reset();

	// Sets mpCurrentPrim to a Primitive type
	void CreatePrimitive(CPrimitive* pPrim);
	void CreatePrimitive(const PrimType::Type primType);

	// Enable/disable reading verticies into the current primitive
	void EnableReading();
	void DisableReading();

	// Sets the current normal that read in verts take on
	void SetCurrentNormal(const CVector3& norm);

	void SetMaterial(Material::Type type, const CColor& color);
	void SetMaterialShine(float shine);
	const CMaterial& GetCurrentMaterial() const { return mCurrentMaterial; }
	
	// Add a vertex to the current primitive.
	// If the current primitive has the max amount of verticies
	// it is added to the list and a new primitive is allocated.
	void AddVertex(const CVertex2& vert);

	// New overloaded version to work with 3D verticies.
	void AddVertex(CVertex3& vert);

	// Clears the current primitive
	void ClearPrimitive();

	// Clears mPrimList
	void ClearAll();

	// Calls Draw() on each primitve in the primitiveList
	void DrawAll();

	// Accessors
	const CPrimitive* GetCurrentPrimitive() const;

private:
	// Adds a valid primitive to mPrimitiveList.
	// Transfers ownership to PrimManager
	void AddPrimitive(PrimPtr& pPrim);

	// Verifies the integrity of the current primtive
	// DEPRECATED
	void VerifyCurrentPrimitive();

	// Applies the matrix in MatrixManager to the 2D primitives
	void Apply2DTransformations();

	// Applies all transformations for 3D verticies (up to clipping stage)
	void Apply3DTransformations();

	// Ensures everything that will be drawn is within the viewport.
	void CullAndClip();

	// Sorts the primitives in ascending Z order
	void DepthSort();

private:
	// Static instance
	static PrimManager* spInstance;
	
	bool mReadingVerticies;		// Read in verts are added to current prim
	PrimPtr mpCurrentPrim;		// Current primitive being drawn
	PrimList mPrimitiveList;	// List of complete primitives to be drawn
	VertList mVertList;			// 3D verticies
	CVector3 mCurrentNormal;	// Normal of the verts being read in
	bool mNormalInitialized;	// Normal was explicitly declared in script
	CMaterial mCurrentMaterial;
};

#endif