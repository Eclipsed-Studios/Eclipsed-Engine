#pragma once

#include <variant>

#include "AssetEngine/Models/AssetType.h"
#include "AssetEngine/Models/AssetDatas/Binary/TextureBinaryData.h"

namespace Eclipse::Assets
{
	struct ImportedAsset
	{
		AssetType type;
		std::variant<TextureBinaryData> data;
		bool succesful = false;
	};
}