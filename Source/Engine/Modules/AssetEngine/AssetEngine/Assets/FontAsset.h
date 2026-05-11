#pragma once

#include "AssetEngine/Assets/Asset.h"
 
#include "AssetEngine/BinaryFormats/FontData.h"
namespace Eclipse::Assets
{
	struct Font : public Asset<FontData> {
		ASSET_IMPL(Font, FontData)

	public:
	};
}