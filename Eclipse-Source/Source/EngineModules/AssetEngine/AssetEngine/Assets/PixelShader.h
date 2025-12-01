#pragma once

#include "Shader.h"

namespace Eclipse
{
	namespace Assets
	{
		struct ShaderHandle;
		class ShaderManager;
	}

	class PixelShader final : public Shaders
	{
		using Shaders::Shaders;
		using Shaders::operator=;
	};
}