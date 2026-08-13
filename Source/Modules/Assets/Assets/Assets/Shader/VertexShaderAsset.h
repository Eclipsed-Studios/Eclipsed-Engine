#pragma once

#include "ShaderAsset.h"
#include "Assets.Core.hpp"

namespace Eclipse::Assets
{
	struct ASSET_API VertexShader : public Shader
	{
		ASSET_IMPL(VertexShader, ShaderData)

	public:
		unsigned GetProgramID() const;

		void Bind();
	};
}