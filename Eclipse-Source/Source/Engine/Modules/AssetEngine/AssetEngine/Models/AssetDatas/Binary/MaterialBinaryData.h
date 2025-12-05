#pragma once

#include "CoreEngine/Math/Color.h"

namespace Eclipse::Assets 
{
	struct MaterialBinaryData
	{
		size_t textureID = 0;
		size_t vertexShaderID = 0;
		size_t pixelShaderID = 0;

		Math::Color color;
	};
};