#pragma once

#include "AssetEngine/AssetCooker/TypeCookers/TypeCooker.h"
#include "AssetEngine/Models/AssetDatas/Binary/TextureBinaryData.h"
#include <string>
#include <unordered_map>


namespace Eclipse::Assets
{
	class TextureCooker : public TypeCooker<TextureBinaryData>
	{
	public:
		void Cook(const TextureBinaryData& data, CookedAsset& outData) override;
	};
}