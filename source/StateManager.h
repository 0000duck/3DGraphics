// ----------------------------------------------------------------------------
//	File: StateManager.h
//	Created by: Tyler Staples
//	Date created: 6/10/2014
//	Description: 
//		Keeps track of the current rendering state which includes
//		the fill mode and draw color.
//		To use this class, use the static accessor by calling StateManager::Instance().
// ----------------------------------------------------------------------------

#ifndef INCLUDED_STATEMANAGER_H
#define INCLUDED_STATEMANAGER_H
#pragma once

#include "Color.h"
#include "FillModes.h"

class StateManager
{
	// Constructors
	StateManager();
	StateManager(const StateManager&);
	StateManager& operator=(const StateManager&);

public:

	// Singleton accessor
	static StateManager* Instance();

	// Mutators
	void SetFillMode(const FillMode::Mode mode);
	void SetColor(const CColor& color);
	void SetColor(float r, float g, float b);
	void StartDrawing();
	void StopDrawing();

	// Accessors
	const FillMode::Mode GetFillMode() const;
	const CColor& GetColor() const;
	bool IsDrawing();

private:
	static StateManager* spInstance;	// Static instance

	FillMode::Mode mFillMode;			// Current fill mode
	CColor mColor;						// Current fill color

	// True when a drawbegin command executes and false
	// when drawend is read
	bool mIsDrawing;
};

#endif