#pragma once

#include "AssetData.h"

#include "Core/FontData.h"

namespace Eclipse::Assets
{
	struct FontData : public AssetData {
		InternalFont font;

		//void LoadNewFontSize();
	};
}
