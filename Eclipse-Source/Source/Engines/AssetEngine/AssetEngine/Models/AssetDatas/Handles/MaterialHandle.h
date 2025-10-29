#pragma once

#include "AssetHandle.h"

#include "AssetEngine/Assets/Texture.h"
#include "Utilities/Math/Color.h"

namespace Eclipse::Assets 
{
	struct MaterialHandle : public AssetHandle
	{
		Textures texture;

		Math::Color color;
	};
};