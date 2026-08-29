#pragma once

#include "Core/Math/Color.h"
#include <vector>

class HatManager 
{
public:
	static void AddHat(const Eclipse::Math::Color& color);
	static const Eclipse::Math::Color& CycleNextHat();

	static const Eclipse::Math::Color& GetCurrentHat();

	static bool HasHats();

	static void Reset();

private:
	static inline int hatIndex = 0;
	static inline std::vector<Eclipse::Math::Color> hats;
};