#include "Stdafx.h"
#include "StateManager.h"
#include <cassert>

// static singleton member initialization
StateManager* StateManager::spInstance = nullptr;

// --------------------------------------------------------------------

// Singleton accessor
StateManager* StateManager::Instance()
{
	if (!spInstance)
	{
		spInstance = new StateManager();
	}
	return spInstance;
}
// --------------------------------------------------------------------

void StateManager::DestroyInstance()
{
	if (spInstance)
	{
		delete spInstance;
		spInstance = nullptr;
	}
}
// --------------------------------------------------------------------

// Default constructor
StateManager::StateManager()
	:	mFillMode(FillMode::Point)
	,	mColor(CColor(1.0, 1.0, 1.0))
	,	mIsDrawing(false)
{
}
// --------------------------------------------------------------------

void StateManager::Reset()
{
	mFillMode = FillMode::Point;
	mColor = CColor(1.0, 1.0, 1.0);
	mIsDrawing = false;
}
// --------------------------------------------------------------------

void StateManager::SetFillMode(const FillMode::Mode mode)
{
	if (mode != FillMode::Invalid)
	{
		mFillMode = mode;
	}
}
// --------------------------------------------------------------------

void StateManager::SetColor(const CColor& color)
{
	if (color.IsValid())
	{
		mColor = color;
	}
}
// --------------------------------------------------------------------

void StateManager::SetColor(float r, float g, float b)
{
	SetColor(CColor(r, g, b));
}
// --------------------------------------------------------------------

void StateManager::StartDrawing()
{
	mIsDrawing = true;
}

void StateManager::StopDrawing()
{
	mIsDrawing = false;
}

const FillMode::Mode StateManager::GetFillMode() const
{
	return mFillMode;
}

// --------------------------------------------------------------------
const CColor& StateManager::GetColor() const
{
	return mColor;
}

bool StateManager::IsDrawing()
{
	return mIsDrawing;
}