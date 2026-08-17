#pragma once

#include "EclipsedEngine/Assets/Asset.h"
 
#include "EclipsedEngine/Assets/BinaryFormats/FontData.h"

namespace Eclipse::Assets
{
	struct ECL_API Font : public Asset<FontData> {
		ASSET_IMPL(Font, FontData)

	public:
	};
}