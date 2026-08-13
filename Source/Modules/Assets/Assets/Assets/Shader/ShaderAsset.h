#pragma once

#include "Assets/Assets/Asset.h"

#include "Assets/BinaryFormats/ShaderData.h"

namespace Eclipse::Assets
{
	struct Shader : public Asset<ShaderData> {
		// methods regarding the asset.
	};
}