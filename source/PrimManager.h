// ----------------------------------------------------------------------------
//	File: PrimManager.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Keeps track of the current primitive being drawn and its verticies.
//		To use this class, use the static accessor by calling StateManager::Instance().
// ----------------------------------------------------------------------------

#ifndef INCLUDED_PRIMMANAGER_H
#define INCLUDED_PRIMMANAGER_H
#pragma once

#include "Primitive.h"
#include <vector>
#include <memory>

class PrimManager
{
	// Constructors
	PrimManager();
	PrimManager(const PrimManager&);
	PrimManager& operator=(const PrimManager&);

public:
	typedef std::vector<std::unique_ptr<CPrimitive>> PrimList;

	// Singleton accessor
	static PrimManager* Instance();

	// Sets mpCurrentPrim to a Primitive type
	void CreatePrimitive(CPrimitive* pPrim);
	void CreatePrimitive(const PrimType::Type primType);

	// Enable/disable reading verticies into the current primitive
	void EnableReading();
	void DisableReading();
	
	// Add a vertex to the current primitive.
	// If the current primitive has the max amount of verticies
	// it is added to the list and a new primitive is allocated.
	void AddVertex(const CVertex2& vert);

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
	void AddPrimitive(std::unique_ptr<CPrimitive>& pPrim);

	// Verifies the integrity of the current primtive
	void VerifyCurrentPrimitive();

	// Ensures everything that will be drawn is within the viewport.
	void CullAndClip();

private:
	// Static instance
	static PrimManager* spInstance;
	
	// Current primitive being drawn
	std::unique_ptr<CPrimitive> mpCurrentPrim;

	// List of complete primitives to be drawn
	PrimList mPrimitiveList;

	// When true, allow verticies to be added to the current primitive
	bool mReadingVerticies;		
};

#endif