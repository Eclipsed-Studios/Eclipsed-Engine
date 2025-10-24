#pragma once

#include "Asset.h"
#include "AssetEngine/Models/AssetDatas/Handles/TextureHandle.h"

namespace Eclipse
{
	class Textures final
	{
		ASSET_IMPL(Textures, Assets::TextureHandle, TextureManager)
	};
}