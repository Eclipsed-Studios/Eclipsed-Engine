#pragma once

#include "CompanionInteractable.h"

class CompanionInteractableManager
{
public:
	static void AddInteractable(CompanionInteractable* interactable);

	static CompanionInteractable* GetClosestInteractable(const Eclipse::Math::Vector2f& playerPos);

	static void Reset();

private:
	static inline std::vector<CompanionInteractable*> interactables;
};