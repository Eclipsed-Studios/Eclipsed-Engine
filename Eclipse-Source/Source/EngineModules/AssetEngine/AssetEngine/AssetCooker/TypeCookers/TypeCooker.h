#pragma once

#include "AssetEngine/AssetCooker/CookedAsset.h"

namespace Eclipse
{
	template<typename T>
	class TypeCooker
	{
	public:
		virtual void Cook(const T& data, CookedAsset& outData) = 0;
	};
}