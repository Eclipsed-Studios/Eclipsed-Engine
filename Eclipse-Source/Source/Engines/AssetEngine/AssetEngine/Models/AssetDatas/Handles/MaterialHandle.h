#pragma once

#include "AssetHandle.h"

#include "AssetEngine/Assets/Texture.h"
#include "AssetEngine/Assets/VertexShader.h"
#include "AssetEngine/Assets/PixelShader.h"
#include "Utilities/Math/Color.h"

namespace Eclipse::Assets 
{
	struct MaterialHandle : public AssetHandle
	{
		Textures texture;

		PixelShaders ps;
		VertexShaders vs;

		Math::Color color;

		unsigned programID;
	};
};