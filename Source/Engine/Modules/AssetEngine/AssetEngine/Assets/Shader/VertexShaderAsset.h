#pragma once

#include "ShaderAsset.h"

namespace Eclipse::Assets
{
	struct VertexShader : public Shader
	{
		ASSET_IMPL(VertexShader, ShaderData)

	public:
		unsigned GetProgramID() const;

		void Bind();
	};
}