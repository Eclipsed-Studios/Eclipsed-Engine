#pragma once

#include "ShaderAsset.h"
#include "EclipsedEngine.Core.hpp"

namespace Eclipse::Assets
{
	struct ECL_API VertexShader : public Shader
	{
		ASSET_IMPL(VertexShader, ShaderData)

	public:
		unsigned GetProgramID() const;
	};
}