#pragma once

#include "AssetHandle.h"

namespace Eclipse::Assets 
{
	struct TextureHandle : public AssetHandle
	{
		int width = 0, height = 0;
		int channels;

		unsigned textureID = 0;
	};
};