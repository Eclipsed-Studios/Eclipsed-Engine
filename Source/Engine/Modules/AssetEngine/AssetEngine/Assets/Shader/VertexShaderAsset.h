#pragma once

#include "ShaderAsset.h"

namespace Eclipse::Assets
{
	struct VertexShader : public Shader
	{
	public:
		unsigned GetProgramID() const;

		void Bind();
	};
}