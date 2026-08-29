#include "HatManager.h"

void HatManager::AddHat(const Eclipse::Math::Color& color)
{
	hats.push_back(color);
	hatIndex = (int)hats.size() -1 ;
}

const Eclipse::Math::Color& HatManager::CycleNextHat()
{
	hatIndex++;
	if (hatIndex >= hats.size())
		hatIndex = 0;

	return GetCurrentHat();
}

const Eclipse::Math::Color& HatManager::GetCurrentHat()
{
	return hats[hatIndex];
}

bool HatManager::HasHats()
{
	return !hats.empty();
}

void HatManager::Reset()
{
	hatIndex = 0;
	hats.clear();
}
