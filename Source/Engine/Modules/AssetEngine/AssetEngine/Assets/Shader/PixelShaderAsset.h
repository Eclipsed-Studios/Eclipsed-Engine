#pragma once

#include "ShaderAsset.h"

namespace Eclipse::Assets
{
	struct PixelShader : public Shader
	{
	public:
		unsigned GetProgramID() const;

		void Bind();
	};
}