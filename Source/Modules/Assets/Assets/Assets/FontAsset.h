#pragma once

#include "Assets/Assets/Asset.h"
 
#include "Assets/BinaryFormats/FontData.h"

namespace Eclipse::Assets
{
	struct ASSET_API Font : public Asset<FontData> {
		ASSET_IMPL(Font, FontData)

	public:
	};
}